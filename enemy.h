//===================================
//
// 敵の処理 [ enemy.h ]
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
#include "objectX.h"

//******************************
// 前方宣言
//******************************
class CShadow;

//******************************
// 敵クラスを定義
//******************************
class CEnemy : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEnemy();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// セッター
	void AddBlow(const D3DXVECTOR3 Vec) { m_move += Vec; }
	void SetBlow(bool isFlags) { m_isBlow = isFlags; }

private:
	D3DXVECTOR3 m_move; // 移動量
	CShadow* m_pShadow; // シャドウ

	bool m_isBlow;		// 吹き飛ばしが有効か
};

