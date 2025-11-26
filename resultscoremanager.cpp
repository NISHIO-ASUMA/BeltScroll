//=======================================================
//
// リザルト用スコア管理処理 [ resultscoremanager.cpp ]
// Author: Asuma Nishio
//
//=======================================================

//**********************
// インクルードガード
//**********************
#include "resultscoremanager.h"
#include "resultscore.h"
#include <fstream>
#include <string>
#include <ostream>
#include "manager.h"
#include "ranking.h"

//=======================================================
// コンストラクタ
//=======================================================
CResultScoreManager::CResultScoreManager()
{
	// 値のクリア
	for (auto& number : m_pResultScore)
	{
		number = nullptr;
	}

	m_nBonusScore = NULL;
	m_nGameScore = NULL;
	m_nLastScore = NULL;
}
//=======================================================
// デストラクタ
//=======================================================
CResultScoreManager::~CResultScoreManager()
{

}
//=======================================================
// 初期化
//=======================================================
HRESULT CResultScoreManager::Init(void)
{
	// 構造体宣言
	Config info = {};

	// ファイル読み込み
	Load();

	// スコアを生成する
	m_pResultScore[info.GAME] = CResultScore::Create(D3DXVECTOR3(1225.0f, 150.0f, 0.0f), 240.0f, 40.0f, 0); // ゲームスコア
	m_pResultScore[info.BONUS] = CResultScore::Create(D3DXVECTOR3(1225.0f,380.0f, 0.0f), 240.0f, 40.0f, 1); // ボーナススコア
	m_pResultScore[info.ALL] = CResultScore::Create(D3DXVECTOR3(1225.0f,  660.0f, 0.0f), 270.0f, 55.0f, 2); // 合計スコア

	// ゲームスコアをセットする
	m_pResultScore[info.GAME]->SetGameScore(m_nGameScore);

	// ボーナススコアをセットする
	m_pResultScore[info.BONUS]->SetBonusScore(m_nBonusScore);

	// 最終スコアをセットする
	m_pResultScore[info.ALL]->SetAllScore(m_nGameScore, m_nBonusScore);

	return S_OK;
}
//=======================================================
// 終了処理
//=======================================================
void CResultScoreManager::Uninit(void)
{

}
//=======================================================
// 更新処理
//=======================================================
void CResultScoreManager::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) ||
		CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) ||
		CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// 最終書き出し
		m_pResultScore[Config::ALL]->WriteScore();

		// ランキングへ遷移
		CManager::GetFade()->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//=======================================================
// テキストファイル読み込み処理
//=======================================================
void CResultScoreManager::Load(void)
{
	// 読み取った値を格納するメンバ変数
	m_nGameScore = NULL;
	m_nBonusScore = NULL;

	//==============================
	// ゲームスコアを読み込む
	//==============================
	std::ifstream file("data/SCORE/GameScore.txt");

	if (file.is_open())
	{
		file >> m_nGameScore;   // 数値1個を読み取り
		file.close();
	}
	else
	{
		MessageBox(NULL, "GameScore.txt が開けませんでした", "エラー", MB_OK);
	}

	//================================
	// ゴミのボーナススコアを読み込む
	//================================
	std::ifstream fileT("data/TrushScore.txt");
	if (fileT.is_open())
	{
		fileT >> m_nBonusScore;    // 数値1個を読み取り
		fileT.close();
	}
	else
	{
		MessageBox(NULL, "TrushScore.txt が開けませんでした", "エラー", MB_OK);
	}
}