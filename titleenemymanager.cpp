//=============================================
//
// タイトルの敵処理 [ titleenemymanager.cpp ]
// Author: Asuma Nishio
//
//=============================================

//****************************
// インクルードガード
//****************************
#include "titleenemymanager.h"
#include <fstream>
#include "json.hpp"
#include "enemy.h"

using json = nlohmann::json; // jsonファイル形式を使用する

//============================
// 初期化処理
//============================
HRESULT CTitleEnemyManager::Init(void)
{
	m_pEnemy.clear();

	Load();

	return S_OK;
}
//============================
// 終了処理
//============================
void CTitleEnemyManager::Uninit(void)
{
	m_pEnemy.clear();
}
//============================
// 読み込み処理
//============================
void CTitleEnemyManager::Load(void)
{
	// 開くファイル
	std::ifstream file("data/JSON/TitleEnemy.json");

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
	for (auto Enemy : m_pEnemy)
	{
		if (Enemy != nullptr)
		{
			// 敵の終了処理
			Enemy->Uninit();
		}
	}

	// 動的配列を空にする
	m_pEnemy.clear();

	// SetObjectsの配列を回す
	for (const auto& b : j["SetObjects"])
	{
		// パス情報
		std::string filepath = b["filepath"];
		int idx = b["idx"];

		// ゴミ自体の種類(重さ)
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
		CEnemy* pEnemy = CreateManagerT(pos, rot, filepath.c_str(), nMassType, nColorType);
	}

}
//===============================
// 生成
//===============================
CEnemy* CTitleEnemyManager::CreateManagerT(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pModelName, int nMass, int nColor)
{
	// 敵生成
	CEnemy* pNewEnemy = CEnemy::Create(pos, rot, pModelName, nMass, nColor);

	// 配列追加
	if (pNewEnemy)
	{
		PushBack(pNewEnemy);
	}

	return pNewEnemy;
}