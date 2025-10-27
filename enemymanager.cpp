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
#include <iostream>
#include <sstream>

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
	if (FAILED(pManager->Init())) return nullptr;

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

	// ローカル変数
	std::string line;
	int nNumFile = NULL;

	// 配列のクリア処理
	m_SubListFiles.clear();

	// 読み込み終わりまで回す
	while (std::getline(openfile, line))
	{
		// 一行読む
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		// "="読み取り
		if (token == "WAVES")
		{
			std::string eq;
			iss >> eq >> nNumFile;

			// ファイル配列のサイズを確保
			m_SubListFiles.resize(nNumFile);
		}
		// "FILE"読み取り時
		else if (token == "FILE")
		{
			// パスと"="を代入
			std::string eq, filepath;

			// ファイルパスを変数に格納
			iss >> eq >> filepath;

			// 動的配列に追加
			m_SubListFiles.push_back(filepath);
		}
	}

	// ファイルを閉じる
	openfile.close();
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