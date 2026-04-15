//=========================================================
//
// 敵管理処理 [ enemymanager.cpp ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "enemymanager.h"
#include "enemy.h"
#include "json.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

//*********************************************************
// 名前空間定義
//*********************************************************
using json = nlohmann::json; // jsonファイル形式を使用する

//=========================================================
// コンストラクタ
//=========================================================
CEnemyManager::CEnemyManager() : m_nCount(NULL),
m_pEnemys{},
m_EnemyData{}
{
}
//=========================================================
// デストラクタ
//=========================================================
CEnemyManager::~CEnemyManager()
{
	Uninit();
}
//=========================================================
// 生成処理
//=========================================================
CEnemyManager* CEnemyManager::Create(void)
{
	// インスタンス生成
	CEnemyManager* pManager = new CEnemyManager;
	if (pManager == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pManager->Init())) return nullptr;

	return pManager;
}
//=========================================================
// 生成処理
//=========================================================
CEnemy* CEnemyManager::CreateEnemy(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const char* pModelName, int nType, int nColorType)
{
	// インスタンス生成
	CEnemy* pEnemy = CEnemy::Create(pos,rot,pModelName,nType, nColorType);

	if (pEnemy)
	{
		// 配列格納
		PushBack(pEnemy);
	}

	return pEnemy;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CEnemyManager::Init(void)
{
	// 読み込み
	CEnemyManager::LoadJson();

	// 初期化処理
	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CEnemyManager::Uninit(void)
{
	// 破棄
	m_pEnemys.clear();
	m_EnemyData.clear();
}
//=========================================================
// 更新処理
//=========================================================
void CEnemyManager::Update(void)
{

}
//=========================================================
// jsonファイル読み込み
//=========================================================
void CEnemyManager::LoadJson(void)
{
	// 開くファイル
	std::ifstream file("data/JSON/EnemyData.json");

	// 開け無かった
	if (!file.is_open())
	{
		// 例外
		MessageBox(nullptr, "ファイルの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR);

		// 終了
		return;
	}

	// jsonから取得する
	json j;
	file >> j;

	// ファイルを閉じる
	file.close();

	// 既存の敵を消す
	for (auto Enemy : m_pEnemys)
	{
		if (Enemy != nullptr)
		{
			// 敵の終了処理
			Enemy->Uninit();
		}
	}

	// 動的配列を空にする
	m_pEnemys.clear();

	// SetObjectsの配列を回す
	for (const auto& b : j["SetObjects"])
	{
		// パス情報
		std::string filepath = b["filepath"];
		int idx = b["idx"];

		// ゴミ自体の種類
		int nMassType = b["mass"];

		// 色の種類
		int nColorType = b["color"];

		// 座標
		D3DXVECTOR3 pos
		(
			b["pos"][0],
			b["pos"][1],
			b["pos"][2]
		);

		// 角度
		D3DXVECTOR3 rot
		(
			b["rot"][0],
			b["rot"][1],
			b["rot"][2]
		);
		// 読み込んだ情報から敵を生成
		CEnemy* pEnemy = CreateEnemy(pos, rot,filepath.c_str(), nMassType, nColorType);
	}
}