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
	m_EnemyData.clear();
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
	// 読み込み
	CEnemyManager::LoadFile();

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
	m_EnemyData.clear();
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
	std::ifstream openfile("data/SCRIPT/EnemySystem.txt");
	if (!openfile)
	{
		MessageBox(GetActiveWindow(), "ファイルが見つかりません", "data/SCRIPT/EnemySystem.txt", MB_OK);
		return;
	}

	std::string line;
	int nNumEnemy = 0;
	bool inBlock = false;

	// 配列初期化
	ENEMYDATA current{};
	m_EnemyData.clear();

	//==============================
	// ファイルを1行ずつ解析
	//==============================
	while (std::getline(openfile, line))
	{
		// コメント除去
		if (line.find('#') != std::string::npos)
			line = line.substr(0, line.find('#'));

		// 空行スキップ
		if (line.empty())
			continue;
		
		// 読み込むライン
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_ENEMY")
		{
			std::string eq;
			iss >> eq >> nNumEnemy;

			// サイズ確保
			m_EnemyData.reserve(nNumEnemy);
		}
		else if (token == "START")
		{
			inBlock = true;
			current = ENEMYDATA(); // 構造体初期化
		}
		else if (token == "END")
		{
			// リストへ格納
			inBlock = false;
			m_EnemyData.push_back(current);
		}
		else if (token == "POS" && inBlock)
		{
			std::string eq; float x, y, z;

			iss >> eq >> x >> y >> z;

			// 座標設定
			current.pos = D3DXVECTOR3(x, y, z);
		}
		else if (token == "ROT" && inBlock)
		{
			std::string eq; 
			float x, y, z;

			iss >> eq >> x >> y >> z;

			// 角度設定
			current.rot = D3DXVECTOR3(x, y, z);
		}
		else if (token == "TYPE" && inBlock)
		{
			std::string eq; 
			int type;
			
			iss >> eq >> type;

			// 種類設定
			current.nType = type;
		}
		else if (token == "FILEPATH" && inBlock)
		{
			std::string eq, path;
			iss >> eq >> path;

			// モデルパス設定
			current.Modelname = path;
		}
		else if (token == "END_FILE")
		{
			break;
		}
	}

	// ファイルを閉じる
	openfile.close();

	//==============================
	// 実際に敵を出現させる
	//==============================
	for (const auto& data : m_EnemyData)
	{
		// 読み取ったデータから作成
		CEnemy* pEnemy = CEnemy::Create
		(
			data.pos,
			data.rot,
			data.Modelname.c_str(),
			data.nType
		);

		// 動的配列に追加
		if (pEnemy)
			m_pEnemys.push_back(pEnemy);
	}
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