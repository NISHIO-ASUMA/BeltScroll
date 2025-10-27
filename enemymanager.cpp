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
#include <fstream>

//==============================
// コンストラクタ
//==============================
CEnemyManager::CEnemyManager()
{
	// 値のクリア
	m_nCount = NULL;
	m_pEnemys.clear();
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
	// 初期敵生成 ( のちにスクリプト変更 )
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/obj/fish.x");
	CEnemy::Create(D3DXVECTOR3(-550.0f, 0.0f, -550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/obj/kan.x");
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), VECTOR3_NULL, "data/MODEL/obj/fish.x");
	CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), VECTOR3_NULL, "data/MODEL/obj/kan.x");

	// 初期化処理
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CEnemyManager::Uninit(void)
{
	// 破棄
	m_pEnemys.clear();
}
//==============================
// 更新処理
//==============================
void CEnemyManager::Update(void)
{
	// のちに時間によって出現 または 場面ごとに出す敵をここで呼び出す
}
//==============================
// ファイル読み込み
//==============================
void CEnemyManager::LoadFile(void)
{
	// 開くファイルをセット
	std::ifstream openfile("data/SCRIPT/EnemySystem.txt");
	if (!openfile)
	{
		// 例外
		MessageBox(GetActiveWindow(), "ファイルが見つかりません", "data/SCRIPT/EnemySystem.txt", MB_OK);
		return;
	}

	// 使用変数

}
//==============================
// 分割ファイル読み込み
//==============================
void CEnemyManager::LoadSplit(const char* pFileName)
{
	// 開くファイルをセット
	std::ifstream opensplit(pFileName);
	if (!opensplit)
	{
		// 例外
		MessageBox(GetActiveWindow(), "このファイルパスはありません", "読み込みエラー", MB_OK);
		return;
	}
}