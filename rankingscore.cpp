//=====================================
//
// ランキングスコア処理 [ rankingscore.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "rankingscore.h"
#include "number.h"
#include <fstream>

//===================================
// コンストラクタ
//===================================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// 値をクリアする
	m_pos = VECTOR3_NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	
	for (int nCnt = 0;nCnt < MAX_RANK;nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_DIGIT; nNumber++)
		{
			m_apNumbers[nCnt][nNumber] = nullptr;
		}
	}

	for (auto& randata : m_RankData)
	{
		randata = NULL;
	}
}
//===================================
// デストラクタ
//===================================
CRankingScore::~CRankingScore()
{
	// 特になし
}
//===================================
// 生成処理
//===================================
CRankingScore* CRankingScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// インスタンス生成
	CRankingScore* pRankScore = new CRankingScore;

	// オブジェクト設定
	pRankScore->m_pos = pos;
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight = fHeight;

	// 初期化失敗時
	if (FAILED(pRankScore->Init()))
	{
		return nullptr;
	}
	
	// 生成されたポインタ
	return pRankScore;
}
//===================================
// 初期化処理
//===================================
HRESULT CRankingScore::Init(void)
{
	// スコアのロード処理
	Load();

	// 横幅計算
	float fTexPos = m_fWidth / MAX_DIGIT;

	for (int nRank = 0; nRank < MAX_RANK; nRank++)
	{
		// 桁数分
		for (int nDigit = 0; nDigit < MAX_DIGIT; nDigit++)
		{
			// インスタンス生成
			m_apNumbers[nRank][nDigit] = new CNumber;

			// Y座標をずらす
			float yOffset = m_pos.y + (m_fHeight + 65.0f) * nRank;

			// 初期化処理
			m_apNumbers[nRank][nDigit]->Init
			(
				D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nDigit), yOffset, 0.0f),
				fTexPos,
				m_fHeight
			);

			// サイズ設定
			m_apNumbers[nRank][nDigit]->SetSize(fTexPos, m_fHeight);

			// テクスチャ設定
			m_apNumbers[nRank][nDigit]->SetTexture("score001.png");
		}
	}

	return S_OK;
}
//===================================
// 終了処理
//===================================
void CRankingScore::Uninit(void)
{
	// nullチェック
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_DIGIT; nNumber++)
		{
			if (m_apNumbers[nCnt][nNumber] != nullptr)
			{
				// 終了処理
				m_apNumbers[nCnt][nNumber]->Uninit();

				// ポインタの破棄
				delete m_apNumbers[nCnt][nNumber];

				// null初期化
				m_apNumbers[nCnt][nNumber] = nullptr;
			}
		}
	}

	// 自身の破棄
	CObject::Release();
}
//===================================
// 更新処理
//===================================
void CRankingScore::Update(void)
{
	// 桁数更新
	for (int rank = 0; rank < MAX_RANK; rank++)
	{
		int nScore = m_RankData[rank];

		for (int digit = 0; digit < MAX_DIGIT; digit++)
		{
			int nNum = nScore % 10;
			nScore /= 10;

			// 桁更新
			m_apNumbers[rank][digit]->SetDigit(nNum);
		}
	}
}
//===================================
// 描画処理
//===================================
void CRankingScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int nCntdigit = 0; nCntdigit < MAX_DIGIT; nCntdigit++)
		{
			// 数字を描画
			m_apNumbers[nCnt][nCntdigit]->Draw();
		}
	}
}
//===================================
// 読込処理
//===================================
void CRankingScore::Load()
{
	// 開くファイルを選択
	std::ifstream OpenFile("data/SCORE/Ranking.txt");
	if (!OpenFile)
	{
		// 例外処理
		MessageBox(GetActiveWindow(), "ファイルが開けません", "Ranking.txt", MB_OK);
		return;
	}

	// 読み込んだデータを格納
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (!(OpenFile >> m_RankData[nCnt]))
		{
			// 数値が無かったら0を入れる
			m_RankData[nCnt] = 0;
		}
	}

	// ファイルを閉じる
	OpenFile.close();
}