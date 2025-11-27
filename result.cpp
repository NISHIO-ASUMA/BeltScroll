//====================================
//
// リザルトシーン処理 [ result.cpp ]
// Author: Asuma Nishio
// 
//====================================

//**************************
// インクルードファイル宣言
//**************************
#include "result.h"
#include "ui.h"
#include "manager.h"
#include "ranking.h"
#include "winplayer.h"
#include "meshfield.h"
#include "ui.h"
#include "resultscore.h"
#include "resultenemy.h"
#include "resultscoremanager.h"
#include "block.h"
#include "resulttrush.h"
#include "resultui.h"
#include "resultobject.h"

//=================================
// 静的メンバ変数
//=================================
CResultScoreManager* CResult::m_pResultScoreManager = nullptr; // スコア管理

//=================================
// オーバーロードコンストラクタ
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT), m_pResultEnemy(nullptr), m_pResultBlock(nullptr)
{

}
//=================================
// デストラクタ
//=================================
CResult::~CResult()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CResult::Init(void)
{
	// カメラ初期化
	CCamera* pCamera = CManager::GetCamera();
	pCamera->Init();

	// 勝利プレイヤー生成
	CWinPlayer::Create(D3DXVECTOR3(80.0f,0.0f,-450.0f));

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3100.0f, 2000.0f, 1, 1);

	// UI生成
	CUi::Create(D3DXVECTOR3(1050.0f, 360.0f, 0.0f), 0, 360.0f, 720.0f, "backboard.png", false);
	CUi::Create(D3DXVECTOR3(200.0f, 60.0f, 0.0f), 0, 200.0f, 60.0f, "clear_resultui.png", false);

	// 敵生成
	m_pResultEnemy = new CResultEnemy;
	m_pResultEnemy->Init("data/JSON/ResultEnemy.json");

	// スコア管理クラス生成
	m_pResultScoreManager = new CResultScoreManager;
	m_pResultScoreManager->Init();

	// 演出ui生成
	CResultUi::Create(D3DXVECTOR3(1200.0f,70.0f,0.0f),150.0f,35.0f,"gamescore.png");
	CResultUi::Create(D3DXVECTOR3(1200.0f, 315.0f, 0.0f), 150.0f, 35.0f, "Bounsscore.png");
	CResultUi::Create(D3DXVECTOR3(1200.0f, 585.0f, 0.0f), 150.0f, 35.0f, "allscore.png");

	// リザルト背景ブロック生成
	m_pResultBlock = new CResultBlock;
	m_pResultBlock->Init("data/JSON/ResultMap.json");

	// 演出用ゴミ箱生成
	CResultTrush::Create(D3DXVECTOR3(-70.0f,0.0f,-440.0f),VECTOR3_NULL, D3DCOLOR_RGBA(255, 215, 0, 255));
	CResultTrush::Create(D3DXVECTOR3(0.0f, 0.0f, -520.0f), VECTOR3_NULL, D3DCOLOR_RGBA(220, 20, 60, 255));
	CResultTrush::Create(D3DXVECTOR3(-140.0f, 0.0f, -520.0f), VECTOR3_NULL, D3DCOLOR_RGBA(0, 191, 255,255));

	// サウンド再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResult::Uninit(void)
{
	// ポインタの破棄
	if (m_pResultEnemy)
	{
		m_pResultEnemy->Uninit();
		delete m_pResultEnemy;
		m_pResultEnemy = nullptr;
	}

	// ポインタの破棄
	if (m_pResultScoreManager)
	{
		m_pResultScoreManager->Uninit();
		delete m_pResultScoreManager;
		m_pResultScoreManager = nullptr;
	}

	// ポインタの破棄
	if (m_pResultBlock)
	{
		m_pResultBlock->Uninit();
		delete m_pResultBlock;
		m_pResultBlock = nullptr;
	}
}
//=================================
// 更新処理
//=================================
void CResult::Update(void)
{
	// 管理クラスの更新処理
	if (m_pResultScoreManager)
	{
		m_pResultScoreManager->Update();
	}
}
//=================================
// 描画処理
//=================================
void CResult::Draw(void)
{
	// 無し
}