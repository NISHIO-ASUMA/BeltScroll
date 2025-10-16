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
	int m_nCount; // 出現カウント
};