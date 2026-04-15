//=========================================================
//
// ゲームシーン管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "gamemanager.h"
#include "meshfield.h"
#include "ui.h"
#include "manager.h"
#include "result.h"
#include "player.h"
#include "blockmanager.h"
#include "shredder.h"
#include "enemymanager.h"
#include "trushSim.h"
#include "gimmickfloor.h"
#include "shreddermanager.h"
#include "loseresult.h"
#include "goal.h"
#include "confettiparticle.h"
#include "combo.h"
#include "trushbox.h"
#include "score.h"
#include "shredderPanel.h"
#include "goalmanager.h"
#include "siren.h"
#include "goalline.h"

//=========================================================
// コンストラクタ
//=========================================================
CGameManager::CGameManager() : m_pBlockManager(nullptr),
m_pPlayer(nullptr),
m_pEnemyManager(nullptr),
m_pTrushSim(nullptr),
m_pGoal(nullptr),
m_pScore(nullptr),
m_pGoalManager(nullptr),
m_pLine(nullptr)
{
}
//=========================================================
// デストラクタ
//=========================================================
CGameManager::~CGameManager()
{
	
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGameManager::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetSound();

	//メッシュフィールド生成
	CMeshField::Create(D3DXVECTOR3(2500.0f,0.0f,0.0f), 8500.0f, 1000.0f, 1, 1);

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player.txt");

	// 敵管理クラスを定義
	m_pEnemyManager = std::make_unique<CEnemyManager>();
	m_pEnemyManager->Init();

	// マップモデル配置情報生成
	m_pBlockManager = new CBlockManager;
	m_pBlockManager->Init();

	// シュレッダーマネージャー生成
	m_pShredderManaher = new CShredderManager;
	m_pShredderManaher->Init();

	// ゴールマネージャー生成
	m_pGoalManager = new CGoalManager;
	m_pGoalManager->Init();

	// サイレン生成
	m_pSiren = CSiren::Create(D3DXVECTOR3(5510.0f, 15.0f, 20.0f));

	// コンボスコア
	CCombo::Create(D3DXVECTOR3(300.0f,50.0f,0.0f));

	// スコア生成
	m_pScore = CScore::Create(D3DXVECTOR3(760.0f, 650.0f, 0.0f), 130.0f, 50.0f);
	m_pScore->ClearScore();

	// ゴールライン生成
	m_pLine = CGoalLine::Create(D3DXVECTOR3(4700.0f, 0.0f, 0.0f), 100.0f);

	// ゲームBGM再生
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// 初期化結果を返す
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGameManager::Uninit(void)
{
	// nullチェック
	if (m_pBlockManager != nullptr)
	{
		// 終了処理
		m_pBlockManager->Uninit();

		// 破棄
		delete m_pBlockManager;

		// null初期化
		m_pBlockManager = nullptr;
	}

	// 敵マネージャーの破棄
	m_pEnemyManager.reset();

	// シュレッダーマネージャーの破棄
	if (m_pShredderManaher != nullptr)
	{
		// 終了処理
		m_pShredderManaher->Uninit();

		// 破棄
		delete m_pShredderManaher;

		// null初期化
		m_pShredderManaher = nullptr;
	}

	// ゴール管理クラスの破棄
	if (m_pGoalManager)
	{
		m_pGoalManager->Uninit();
		delete m_pGoalManager;
		m_pGoalManager = nullptr;
	}
}
//=========================================================
// 更新処理
//=========================================================
void CGameManager::Update(void)
{
#ifdef _DEBUG

	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F5))
	{
		// 勝ちリザルト
		CManager::GetFade()->SetFade(std::make_unique<CResult>());
		
		return;
	}

	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		// 負けリザルト
		CManager::GetFade()->SetFade(std::make_unique<CLoseResult>());

		return;
	}
#endif

	// nullチェック
	if (m_pEnemyManager != nullptr)
	{
		// 敵管理の更新処理
		m_pEnemyManager->Update();
	}

	// nullチェック
	if (m_pGoalManager != nullptr)
	{
		// ゴール管理の更新処理
		m_pGoalManager->Update();
	}

	// nullチェック
	if (m_pShredderManaher != nullptr)
	{
		// 更新処理
		m_pShredderManaher->Update();
	}
}
//=========================================================
// 描画処理
//=========================================================
void CGameManager::Draw(void)
{

}