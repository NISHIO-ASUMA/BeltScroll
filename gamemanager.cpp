//======================================================
//
// ゲームシーンオブジェクト管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
//
//======================================================

//******************************
// インクルードファイル
//******************************
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

//===============================
// コンストラクタ
//===============================
CGameManager::CGameManager()
{
	// 値のクリア
	m_pBlockManager = nullptr;
	m_pPlayer = nullptr;
	m_pEnemyManager = nullptr;
	m_pTrushSim = nullptr;
	m_pGoal = nullptr;
	m_pScore = nullptr;
}
//===============================
// デストラクタ
//===============================
CGameManager::~CGameManager()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CGameManager::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetSound();

	//メッシュフィールド生成
	CMeshField::Create(D3DXVECTOR3(2500.0f,0.0f,0.0f), 6000.0f, 1000.0f, 1, 1);

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player.txt");

	// 敵管理クラスを定義
	m_pEnemyManager = std::make_unique<CEnemyManager>();
	m_pEnemyManager->Init();

	//// 壁生成
	//m_pTrushSim = CTrushSim::Create(D3DXVECTOR3(0.0f, 30.0f, 0.0f), VECTOR3_NULL, INITSCALE, "data/MODEL/STAGEOBJ/block000.x");

	// マップモデル配置情報生成
	m_pBlockManager = new CBlockManager;
	m_pBlockManager->Init();

	m_pShredderManaher = new CShredderManager;
	m_pShredderManaher->Init();

	// ゴール生成
	m_pGoal = CGoal::Create(D3DXVECTOR3(5500.0f,90.0f,0.0f));

	CTrushBox::Create(D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),"data/MODEL/STAGEOBJ/block000.x" );

	// コンボスコア
	CCombo::Create(D3DXVECTOR3(300.0f,50.0f,0.0f));

	// スコア生成
	m_pScore = CScore::Create(D3DXVECTOR3(1235.0f, 45.0f, 0.0f), 110.0f, 45.0f);
	m_pScore->ClearScore();

	// ゲームBGM
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
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

	if (m_pShredderManaher != nullptr)
	{
		// 終了処理
		m_pShredderManaher->Uninit();

		// 破棄
		delete m_pShredderManaher;

		// null初期化
		m_pShredderManaher = nullptr;
	}
}
//===============================
// 更新処理
//===============================
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
	if (m_pShredderManaher != nullptr)
	{
		// 更新処理
		m_pShredderManaher->Update();
	}
}
//===============================
// 描画処理
//===============================
void CGameManager::Draw(void)
{
	// 描画するものがあればここに追加
	// Object継承の物は書くな
}