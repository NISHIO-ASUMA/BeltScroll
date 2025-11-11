//=======================================
//
// ブロック管理処理 [ blockmanager.cpp ]
// Author: Asuma Nishio
//
//=======================================

//***************************
// インクルードファイル
//***************************
#include "blockmanager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"

//***************************
// 静的メンバ変数
//***************************
std::vector<CBlock*>CBlockManager::m_block = {}; // 動的配列

//***************************
// 使用名前空間
//***************************
using json = nlohmann::json; // jsonファイル形式を使用する

//===========================
// コンストラクタ
//===========================
CBlockManager::CBlockManager()
{
	// 値のクリア
	m_block.clear();
}
//===========================
// デストラクタ
//===========================
CBlockManager::~CBlockManager()
{
	// 無し
}
//===========================
// 初期化処理
//===========================
HRESULT CBlockManager::Init(void)
{
	// 配列を切り離し
	m_block.clear();

	// json開く
	LoadJsonScript("data/JSON/testgame.json");

	// 初期化結果を返す
	return S_OK;
}
//===========================
// 終了処理
//===========================
void CBlockManager::Uninit(void)
{
	// 配列切り離し
	m_block.clear();
}
//===========================
// 更新処理
//===========================
void CBlockManager::Update(void)
{
	// 無し
}
//===========================
// 生成処理
//===========================
CBlock* CBlockManager::CreateManagerBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// インスタンス生成
	CBlock* pManagBlock = CBlock::Create(pos,rot,scale,pModelName);

	if (pManagBlock != nullptr)
	{
		// 配列追加
		m_block.push_back(pManagBlock);
	}

	// 生成された物を返す
	return pManagBlock;
}
//===========================
// 読み込み処理
//===========================
void CBlockManager::LoadJsonScript(const char* jsonName)
{
	// 開くファイル
	std::ifstream file(jsonName);

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

	// 既存のブロックを消す
	for (auto block : m_block)
	{
		if (block != nullptr)
		{
			// ブロックの終了処理
			block->Uninit();
		}
	}

	// 動的配列を空にする
	m_block.clear();

	// SetObjectsの配列を回す
	for (const auto& b : j["SetObjects"])
	{
		std::string filepath = b["filepath"];
		int idx = b["idx"];

		D3DXVECTOR3 pos
		(
			b["pos"][0],
			b["pos"][1],
			b["pos"][2]
		);
		D3DXVECTOR3 rot
		(
			b["rot"][0],
			b["rot"][1],
			b["rot"][2]
		);

		D3DXVECTOR3 scale
		(
			b["scale"][0],
			b["scale"][1],
			b["scale"][2]
		);

		// ブロック生成
		CBlock* block = CreateManagerBlock(pos, rot, scale, filepath.c_str());
	}
}