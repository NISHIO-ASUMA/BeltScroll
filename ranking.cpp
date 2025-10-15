//=======================================
//
// ランキングシーン処理 [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// インクルードファイル宣言
//******************************
#include "ranking.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "ui.h"
#include "rankingscore.h"
#include "number.h"

//******************************
// 静的メンバ変数
//******************************
CRankingScore* CRanking::m_Score[MAX_RANK] = {};

//===================================
// オーバーロードコンストラクタ
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	//CObject::SetObjType(CObject::TYPE_SCENE);

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		//m_Score[nCnt] = NULL;
		m_nNumData[nCnt] = 0;
	}
}
//===================================
// デストラクタ
//===================================
CRanking::~CRanking()
{
	// 無し
}
//===================================
// 生成処理
//===================================
CRanking* CRanking::Create(void)
{
	// インスタンス生成
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pRanking->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pRanking;
}
//===================================
// 初期化処理
//===================================
HRESULT CRanking::Init(void)
{
	//// サウンドへのポインタ(サウンドの取得)
	//CSound* pSound = CManager::GetSound();

	// 順位の数
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_Score[nCnt] = CRankingScore::Create(D3DXVECTOR3(1100.0f, 200.0f + 100.0f * nCnt, 0.0f), 100.0f, 100.0f);
	}

	TxtLoad("data\\Text\\Rank.txt");	// 読込

	SetSort();	// 並び替え

	//// BGMを流す
	//pSound->PlaySound(CSound::SOUND_LABEL_RESULTDATA);

	// ui生成
	CUi::Create(CENTERPOS, 0, 640.0f, 360.0f, "RankBack.jpg", false);

	// 初期化結果を返す
	return S_OK;
}
//===================================
// 終了処理
//===================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_apNumbers[nCnt]->CNumber::Uninit();
	}

}
//===================================
// 更新処理
//===================================
void CRanking::Update(void)
{
	// 決定キー入力
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// 画面遷移
		pFade->SetFade(new CTitle());

		return;
	}
}
//===================================
// 描画処理
//===================================
void CRanking::Draw(void)
{
	// 無し
}

//===================================
// ランキングの入替処理(降順)
//===================================
void CRanking::SetSort(void)
{
	//int nScore = CScore::Load("data\\txt\\Score.txt");

	int nNumData[MAX_RANK + 1] = { 0 };	// ランキングスコア格納用

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nNumData[nCnt] = m_nNumData[nCnt];
	}

	//nNumData[MAX_RANK] = nScore;

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nSelect = nCntRank + 1; nSelect < MAX_RANK + 1; nSelect++)
		{
			if (nNumData[nCntRank] < nNumData[nSelect])
			{
				int nRankSave = nNumData[nCntRank];	// 一時保存

				// 数値の入れ替え
				nNumData[nCntRank] = nNumData[nSelect];
				nNumData[nSelect] = nRankSave;
			}
		}
	}

	// ランキングの代入
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_nNumData[nCnt] = nNumData[nCnt];
	}

	// ランキングの保存
	TxtSave("data\\Text\\Rank.txt");
}

//===================================
// ランキングの読込処理
//===================================
void CRanking::TxtLoad(const char* pFileName)
{
	// ファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{
		// 文字列格納用変数
		char aString[32] = {};
		char cData = {};
		int nRank[MAX_RANK] = { 0 };

		while (1)
		{
			cData = fscanf(pFile, "%s", &aString[0]);

			// 何も無かったら
			if ((int)aString[0] == EOF || (char)aString[0] == NULL)
			{
				// ループを抜ける
				break;
			}
			else if (strcmp(&aString[0], "RANKING") == 0)
			{
				// 数字の読み取り
				for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
				{
					cData = fscanf(pFile, "%d", &nRank[nCnt]);
				}
			}
			else if (strcmp(&aString[0], "END_RANKING") == 0)
			{
				// スコアの保存
				for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
				{
					m_nNumData[nCnt] = nRank[nCnt];
				}

				// ファイルを閉じる
				fclose(pFile);

				// ループを抜ける
				break;
			}
		}
	}
}

//===================================
// ランキングの保存処理
//===================================
void CRanking::TxtSave(const char* pFileName)
{
	// ファイルを開く
	FILE* pFile = fopen(pFileName, "w");

	if (pFile != nullptr)
	{
		fprintf(pFile, "RANKING");

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "\n%d", m_nNumData[nCnt]);
		}
	}
}
