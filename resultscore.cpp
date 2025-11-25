//===========================================
//
// リザルト用スコア処理 [ resultscore.cpp ]
// Author: Asuma Nishio
// 
//===========================================

//**********************
// インクルードファイル
//**********************
#include "resultscore.h"
#include "number.h"
#include <fstream>
#include "easing.h"

//=====================
// コンストラクタ
//=====================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_fHeight = NULL;
	m_fWidth = NULL;
	
	m_nLoadScore = NULL;
	m_nBounsScore = NULL;
	m_nMassAllScore = NULL;

	m_nCurrentScore = NULL;	// 今の表示スコア
	m_nStartScore = NULL;	// 開始時のスコア
	m_nTargetScore = NULL;	// ゴールのスコア
	m_nTimer = NULL;		// 経過フレーム
	m_nDuration = NULL;		// 目的の時間

	nType = NULL;

	for (auto& number : m_pNumber)
	{
		number = nullptr;
	}
}
//=====================
// デストラクタ
//=====================
CResultScore::~CResultScore()
{
	// 無し
}
//=====================
// 生成処理
//=====================
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// インスタンス生成
	CResultScore* presult = new CResultScore;
	if (presult == nullptr) return nullptr;

	// 値をセット
	presult->m_pos = pos;
	presult->m_fHeight = fHeight;
	presult->m_fWidth = fWidth;
	presult->nType = nType;

	// 初期化失敗時
	if (FAILED(presult->Init())) 	return nullptr;

	// 生成されたインスタンス
	return presult;
}
//=====================
// 初期化処理
//=====================
HRESULT CResultScore::Init(void)
{
	// 横の分割幅を計算
	float fTexPos = m_fWidth / RESULT_SCORE;

	// ナンバー生成
	for (int nCnt = 0; nCnt < RESULT_SCORE; nCnt++)
	{
		// ナンバーオブジェクトの生成
		m_pNumber[nCnt] = new CNumber;

		// 初期化処理
		m_pNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);

		// ナンバー変数のサイズ
		m_pNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// 座標設定
		m_pNumber[nCnt]->SetPos(m_pos);

		// テクスチャセット
		m_pNumber[nCnt]->SetTexture("result_score.png");
	}

	return S_OK;
}
//=====================
// 終了処理
//=====================
void CResultScore::Uninit(void)
{
	// nullチェック
	for (auto& number : m_pNumber)
	{
		if (number != nullptr)
		{
			// 終了処理
			number->Uninit();

			// ポインタの破棄
			delete number;

			// null初期化
			number = nullptr;
		}
	}

	// 自身の破棄
	CObject::Release();
}
//=====================
// 更新処理
//=====================
void CResultScore::Update(void)
{
	// 種類に応じた更新
	switch (nType)
	{
	case SCORE_GAME:
		UpdateGameScore();
		break;

	case SCORE_BONUS:
		UpdateBounsScore();
		break;

	case SCORE_ALL:
		UpdateLastScore();
		break;

	default:
		break;
	}
}
//=====================
// 描画処理
//=====================
void CResultScore::Draw(void)
{
	// ナンバーオブジェクト描画
	for (int nCnt = 0; nCnt < RESULT_SCORE; nCnt++)
	{
		// ナンバー描画
		m_pNumber[nCnt]->Draw();
	}
}
//=====================
// ゲームスコア更新
//=====================
void CResultScore::UpdateGameScore(void)
{
	// まだアニメ中
	if (m_nTimer < m_nDuration)
	{
		// イージング適用s
		float t = CEasing::SetEase(m_nTimer, m_nDuration);
		float rate = CEasing::EaseOutCubic(t);

		// 現在スコア = 開始 + (目標 - 開始) * イージング補間
		m_nCurrentScore = m_nStartScore + (int)((m_nLoadScore - m_nStartScore) * rate);

		// 加算
		m_nTimer++;
	}
	else
	{
		// 現在スコアに設定
		m_nCurrentScore = m_nLoadScore;
	}

	// 桁数更新
	int nScore = m_nCurrentScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < RESULT_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % NUMBERINFO::NUMBER_DIGIT_VALUE;
		nScore /= NUMBERINFO::NUMBER_DIGIT_VALUE;

		// 更新
		m_pNumber[nCntScore]->Update();

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}
//=====================
// ボーナススコア更新
//=====================
void CResultScore::UpdateBounsScore(void)
{
	// まだアニメ中
	if (m_nTimer < m_nDuration)
	{
		// イージング適用s
		float t = CEasing::SetEase(m_nTimer, m_nDuration);
		float rate = CEasing::EaseOutCubic(t);

		// 現在スコア = 開始 + (目標 - 開始) * イージング補間
		m_nCurrentScore = m_nStartScore + (int)((m_nBounsScore - m_nStartScore) * rate);

		// 加算
		m_nTimer++;
	}
	else
	{
		// 現在スコアに設定
		m_nCurrentScore = m_nBounsScore;
	}

	// 桁数更新
	int nScore = m_nCurrentScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < RESULT_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % NUMBERINFO::NUMBER_DIGIT_VALUE;
		nScore /= NUMBERINFO::NUMBER_DIGIT_VALUE;

		// 更新
		m_pNumber[nCntScore]->Update();

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}
//=====================
// 最終スコア更新
//=====================
void CResultScore::UpdateLastScore(void)
{
	// まだアニメ中
	if (m_nTimer < m_nDuration)
	{
		// イージング適用s
		float t = CEasing::SetEase(m_nTimer, m_nDuration);
		float rate = CEasing::EaseOutCubic(t);

		// 現在スコア = 開始 + (目標 - 開始) * イージング補間
		m_nCurrentScore = m_nStartScore + (int)((m_nMassAllScore - m_nStartScore) * rate);

		// 加算
		m_nTimer++;
	}
	else
	{
		// 現在スコアに設定
		m_nCurrentScore = m_nMassAllScore;
	}

	// 桁数更新
	int nScore = m_nCurrentScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < RESULT_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % NUMBERINFO::NUMBER_DIGIT_VALUE;
		nScore /= NUMBERINFO::NUMBER_DIGIT_VALUE;

		// 更新
		m_pNumber[nCntScore]->Update();

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}

//=====================
// 最終スコア書き出し
//=====================
void CResultScore::WriteScore(void)
{
	// 外部ファイルに書き出す
	std::ofstream OutFile("data/LastScore.txt");
	if (!OutFile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "ファイルが開けません", "LastScore.txt", MB_OK);
		return;
	}

	// 読み取ったデータをセット
	OutFile << m_nMassAllScore << std::endl;

	// ファイルを閉じる
	OutFile.close();
}