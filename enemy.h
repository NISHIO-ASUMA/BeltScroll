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
class CAABBCollider;

//******************************
// 敵クラスを定義
//******************************
class CEnemy : public CObjectX
{
public:
	//***************************
	// ゴミの重さ種類の列挙型
	//***************************
	enum TYPE
	{
		TYPE_NONE,			// なんでも飛ぶ
		TYPE_LIGHTTRUSH,	// 軽い
		TYPE_HEAVYTRUSH,	// 重い
		TYPE_MAX
	};

	//***************************
	// 色種類の列挙型
	//***************************
	enum COLORTYPE
	{
		COLORTYPE_RED,		// 赤
		COLORTYPE_BLUE,		// 青
		COLORTYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEnemy();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CAABBCollider * pOtherCollider);
	bool CollisionToBlock(CAABBCollider * pOther,D3DXVECTOR3 * pOutPos);

	// 静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName,int nTrushType,int nColorType);

	// セッター
	void SetTrushMassType(int trushType) { m_TrushType = trushType; }
	void SetColorType(int nType) { m_nColorType = nType; }
	void AddBlow(const D3DXVECTOR3 Vec) { m_move += Vec; }
	void SetBlow(bool isFlags) { m_isBlow = isFlags; }

	// ゲッター
	int GetType(void) { return m_TrushType; }
	CSphereCollider* GetCollider(void) { return m_pCollider; }

private:
	D3DXVECTOR3 m_move;		// 移動量
	CShadowS* m_pShadowS;	// ステンシルシャドウ
	CSphereCollider* m_pCollider; // コライダー
	CAABBCollider* m_pAABB;	// 矩形のコライダー

	int m_TrushType;		// ゴミ自体の種類
	int m_nColorType;		// 対応するシュレッダーカラーの種類
	bool m_isBlow;			// 吹き飛ばしが有効か

	static constexpr int COLLOBJ = 2; // シュレッダー数
};