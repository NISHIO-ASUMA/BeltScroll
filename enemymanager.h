//===================================
//
// 敵管理処理 [ enemymanager.h ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードガード
//******************************
#pragma once

//******************************
// インクルードファイル
//******************************
#include <vector>

//******************************
// 前方宣言
//******************************
class CEnemy;

//******************************
// 敵管理クラスを定義
//******************************
class CEnemyManager
{
public:
	// コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CEnemyManager* Create(void);

private:

	void LoadFile(void);				   // ファイル読み込み関数
	void LoadSplit(const char* pFileName); // 分割読み込み

	int m_nCount; // 出現カウント

	std::vector<CEnemy*>m_pEnemys;		// 敵の動的配列
};