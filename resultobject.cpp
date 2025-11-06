//================================================
//
// リザルト用ブロック処理 [ resultobject.cpp ]
// Author: Asuma Nishio
//
//================================================

//******************************
// インクルードファイル
//******************************
#include "resultobject.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"
#include "block.h"

//***************************
// 使用名前空間
//***************************
using json = nlohmann::json; // jsonファイル形式を使用する

//=================================
// コンストラクタ
//=================================
CResultBlock::CResultBlock() : m_resultblock{}
{

}
//=================================
// デストラクタ
//=================================
CResultBlock::~CResultBlock()
{
	m_resultblock.clear();
}
//=================================
// 初期化処理
//=================================
HRESULT CResultBlock::Init(void)
{
	// 値のクリア
	m_resultblock.clear();

	// ファイル読み込み
	LoadJson();

	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResultBlock::Uninit(void)
{
	m_resultblock.clear();
}
//=================================
// 更新処理
//=================================
void CResultBlock::Update(void)
{
	// 無し
}
//=================================
// 読み込んだものを生成する関数
//=================================
CBlock* CResultBlock::CreateBlock(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, const char* pModelName)
{
	// インスタンス
	CBlock* pNewBlock = CBlock::Create(pos, rot, scale, pModelName);

	// 配列追加関数
	if (pNewBlock)
	{
		PushBack(pNewBlock);
	}

	return pNewBlock;
}
//=================================
// JSON読み込み
//=================================
void CResultBlock::LoadJson(void)
{
	// 開くファイル
	std::ifstream file("data/JSON/ResultMap.json");

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
	for (auto block : m_resultblock)
	{
		if (block != nullptr)
		{
			// ブロックの終了処理
			block->Uninit();
		}
	}

	// 動的配列を空にする
	m_resultblock.clear();

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
		CBlock* block = CreateBlock(pos, rot, scale, filepath.c_str());
	}
}
