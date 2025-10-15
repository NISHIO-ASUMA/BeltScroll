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
#include "enemy.h"

//===============================
// コンストラクタ
//===============================
CGameManager::CGameManager()
{
	// 値のクリア
	m_pBlockManager = nullptr;
	m_pPlayer = nullptr;
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
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// プレイヤー生成 ( のちにモデル変更 )
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");

	// 敵生成
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");
	CEnemy::Create(D3DXVECTOR3(-550.0f,0.0f,-550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");

	// 生成
	m_pBlockManager = new CBlockManager;
	m_pBlockManager->Init();

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
		CManager::GetFade()->SetFade(new CResult());

		return;
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
