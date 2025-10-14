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

//===================================
// コンストラクタ
//===================================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// 値をクリアする
	m_pos = VECTOR3_NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_ScoreNum = NULL;
	
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumbers[nCnt] = NULL;
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

	pRankScore->m_pos = pos;
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight=fHeight;

	// 初期化処理
	pRankScore->Init();

	return pRankScore;
}

//===================================
// 初期化処理
//===================================
HRESULT CRankingScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumbers[nCnt]->Init(m_pos, m_fWidth, m_fHeight);
	}
	return S_OK;
}

//===================================
// 終了処理
//===================================
void CRankingScore::Uninit(void)
{
	// 今はなし
}

//===================================
// 更新処理
//===================================
void CRankingScore::Update(void)
{
	// 特になし
}

//===================================
// 描画処理
//===================================
void CRankingScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// 数字を描画
		m_apNumbers[nCnt]->CNumber::Draw();
	}
}

//===================================
// 読込処理
//===================================
int CRankingScore::Load(const char* pFileName)
{
	// ファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	int nLoad = { 0 };
	char cData = {};

	if (pFile != NULL)
	{
		// 文字列格納用変数
		char aString[32] = {};

		while (1)
		{
			cData = fscanf(pFile, "%s", &aString[0]);

			// 何も無かったら
			if ((int)aString[0] == EOF || (char)aString[0] == NULL)
			{
				// ファイルを閉じる
				fclose(pFile);

				// ループを抜ける
				break;
			}
		}
	}
	return nLoad;
}