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
class CShadowS;
class CSphereCollider;
class CSphereSphereCollision;

//******************************
// 敵クラスを定義
//******************************
class CEnemy : public CObjectX
{
public:
	//***************************
	// 種類の列挙型
	//***************************
	enum TYPE
	{
		TYPE_NONE,			// 無し
		TYPE_LIGHTTRUSH,	// 軽い
		TYPE_HEAVYTRUSH,	// 重い
		TYPE_ROLLTRUSH,		// 転がる
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEnemy();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CSphereCollider * pOtherCollider);

	// 静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// セッター
	void SetType(int Type) { m_TrushType = Type; }
	void AddBlow(const D3DXVECTOR3 Vec) { m_move += Vec; }
	void SetBlow(bool isFlags) { m_isBlow = isFlags; }

	// ゲッター
	int GetType(void) { return m_TrushType; }
	CSphereCollider* GetCollider(void) { return m_pCollider; }

private:
	D3DXVECTOR3 m_move;		// 移動量
	CShadowS* m_pShadowS;	// ステンシルシャドウ
	int m_TrushType;		// ゴミの種類
	bool m_isBlow;			// 吹き飛ばしが有効か
	CSphereCollider* m_pCollider; // コライダー
};

