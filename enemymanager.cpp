//===================================
//
// 敵管理処理 [ enemymanager.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードファイル
//******************************
#include "enemymanager.h"
#include "enemy.h"

//==============================
// コンストラクタ
//==============================
CEnemyManager::CEnemyManager()
{
	// 値のクリア
	m_nCount = NULL;
}
//==============================
// デストラクタ
//==============================
CEnemyManager::~CEnemyManager()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CEnemyManager* CEnemyManager::Create(void)
{
	// インスタンス生成
	CEnemyManager* pManager = new CEnemyManager;
	if (pManager == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pManager->Init()))
	{
		return nullptr;
	}

	return pManager;
}
//==============================
// 初期化処理
//==============================
HRESULT CEnemyManager::Init(void)
{
	// 初期敵生成
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/enemy000.x");
	CEnemy::Create(D3DXVECTOR3(-550.0f, 0.0f, -550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/enemy000.x");

	// 初期化処理
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CEnemyManager::Uninit(void)
{
	// 今は無し
}
//==============================
// 更新処理
//==============================
void CEnemyManager::Update(void)
{
	// のちに時間によって出現 または 場面ごとに出す敵をここで呼び出す
}