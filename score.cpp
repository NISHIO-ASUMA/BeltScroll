//===================================
//
// スコア処理 [ score.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードファイル
//******************************
#include "score.h"
#include "number.h"
#include "manager.h"
#include <fstream>
#include "game.h"
#include "shreddermanager.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
int CScore::m_nScore = NULL;

//=================================
// コンストラクタ
//=================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_pos = VECTOR3_NULL;
	m_nDrawCount = NULL;
	m_isDraw = false;
	m_hasDrawed = false;

	for (auto& number : m_pNumber)
	{
		number = nullptr;
	}
}
//=================================
// デストラクタ
//=================================
CScore::~CScore()
{
	// 無し
}
//=================================
// 生成処理
//=================================
CScore* CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// インスタンス生成
	CScore* pScore = new CScore;
	if (pScore == nullptr) return nullptr;

	// オブジェクト設定
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;
	pScore->m_pos = pos;

	// 初期化失敗時
	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	// インスタンスを課返す
	return pScore;
}
//=================================
// 初期化処理
//=================================
HRESULT CScore::Init(void)
{
	// 横の分割幅を計算
	float fTexPos = m_fWidth / SCORE_NUM;

	// 桁数分
	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
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

	// スコア初期化
	m_nScore = NULL;

	return S_OK;
}
//=================================
// 終了処理
//=================================
void CScore::Uninit(void)
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

	CObject::Release();
}
//=================================
// 更新処理
//=================================
void CScore::Update(void)
{
	// 座標移動
	m_pos;

	// スコア格納
	int nScore = m_nScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % NUMBERINFO::NUMBER_DIGIT_VALUE;
		nScore /= NUMBERINFO::NUMBER_DIGIT_VALUE;

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}

	// 現在のゴミステーションインデックスを取得
	auto idx = CGame::GetGameManager()->GetShredderM()->GetTrushCount();

	// 中間番号なら
	if (idx == 3 && !m_hasDrawed)
	{
		m_isDraw = true;		// 描画開始
		m_nDrawCount = 0;		// カウントリセット
		m_hasDrawed = true;		// 再度表示しない
	}

	// 表示中ならカウント進める
	if (m_isDraw)
	{
		m_nDrawCount++;

		// 5秒経過したら非表示にする
		if (m_nDrawCount >= 300)
		{
			m_isDraw = false;
		}
	}
}
//=================================
// 描画処理
//=================================
void CScore::Draw(void)
{	
	// 番号が表示番号なら描画をONにする
	if (m_isDraw)
	{
		// 使っている桁数分の描画
		for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
		{
			// ナンバー描画
			m_pNumber[nCnt]->Draw();
		}
	}
}
//=================================
// 書き出し処理
//=================================
void CScore::Save(void)
{
	// 開くファイルをセット
	std::ofstream OpenFile("data/SCORE/GameScore.txt");
	if (!OpenFile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "スコア保存失敗", "ファイルを開けません", MB_OK);
		return;
	}

	// スコア書き出し
	OpenFile << m_nScore;

	// ファイルを閉じる
	OpenFile.close();
}