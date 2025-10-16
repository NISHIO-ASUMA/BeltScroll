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

//===============================
// コンストラクタ
//===============================
CGameManager::CGameManager()
{
	// 値のクリア
	m_pBlockManager = nullptr;
	m_pPlayer = nullptr;
	m_pEnemyManager = nullptr;
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
	//メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 1500.0f, 1, 1);

	// プレイヤー生成 ( のちにモデル変更 )
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");

	// 敵管理クラスを定義
	m_pEnemyManager = CEnemyManager::Create();

	// 壁生成
	CTrushSim::Create(D3DXVECTOR3(-550.0f, 200.0f, 00.0f), VECTOR3_NULL, INITSCALE, "data/MODEL/STAGEOBJ/Shredder.x");
	//// マップモデル配置情報生成
	//m_pBlockManager = new CBlockManager;
	//m_pBlockManager->Init();

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

	// nullチェック
	if (m_pEnemyManager != nullptr)
	{
		// 終了処理
		m_pEnemyManager->Uninit();

		// 破棄
		delete m_pEnemyManager;

		// null初期化
		m_pEnemyManager = nullptr;
	}
}
//===============================
// 更新処理
//===============================
void CGameManager::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ランキング
		CManager::GetFade()->SetFade(std::make_unique<CResult>());

		return;
	}

	// nullチェック
	if (m_pEnemyManager != nullptr)
	{
		// 敵管理の更新処理
		m_pEnemyManager->Update();
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
