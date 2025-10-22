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

//=====================
// コンストラクタ
//=====================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nLoadScore = NULL;

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
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// インスタンス生成
	CResultScore* presult = new CResultScore;
	if (presult == nullptr) return nullptr;

	// 値をセット
	presult->m_pos = pos;
	presult->m_fHeight = fHeight;
	presult->m_fWidth = fWidth;
	
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
	// スコア読み込み
	Load();

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
		m_pNumber[nCnt]->SetTexture("number003.png");
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

	CObject::Release();
}
//=====================
// 更新処理
//=====================
void CResultScore::Update(void)
{
	// 桁数更新
	int nScore = m_nLoadScore;

	// 八桁分
	for (int nCntScore = 0; nCntScore < RESULT_SCORE; nCntScore++)
	{
		// 桁数ごとに分割する値を計算
		int nDigit = nScore % RESULT_SCORE;
		nScore /= RESULT_SCORE;

		// 桁更新
		m_pNumber[nCntScore]->SetDigit(nDigit);
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
// 読み込み処理
//=====================
void CResultScore::Load(void)
{
	// 開くファイルをセット
	std::ifstream OpenFile("data/SCORE/GameScore.txt");
	if (!OpenFile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "ファイルが開けません", "リザルトスコア読み込み", MB_OK);
		return;
	}

	// 読み取ったデータをセット
	OpenFile >> m_nLoadScore;

	// ファイルを閉じる
	OpenFile.close();
}