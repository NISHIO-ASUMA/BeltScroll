//====================================
//
// コリジョン処理 [ collision.cpp ]
// Author: Sasaki Soichiro 
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "collision.h"
#include "collider.h"

//===============================
// コンストラクタ
//===============================
CCollision::CCollision()
{
}
//===============================
// デストラクタ
//===============================
CCollision::~CCollision()
{
	// 無し
}



//===============================
// コンストラクタ
//===============================
CSphereSphereCollision::CSphereSphereCollision()
{
}
//===============================
// デストラクタ
//===============================
CSphereSphereCollision::~CSphereSphereCollision()
{
	// 無し
}

//===============================
// 球と球のあたり判定
//===============================
bool CSphereSphereCollision::Collision(CSphereCollider* me, CSphereCollider* other)
{
	// ポインタ
	CSphereCollider* pMe = me;
	CSphereCollider* pOther = other;

	// 位置取得
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// 半径取得
	float fMeRad = pMe->GetRadius();
	float fOtherRad = pOther->GetRadius();

	// 中心点同士の距離
	D3DXVECTOR3 dist = mePos - otherPos;
	float fDist = D3DXVec3Length(&dist);

	// 半径の合計
	float fRadSum = fMeRad + fOtherRad;

	if (fDist < fRadSum)
	{// 半径の合計をより距離が近い
		return true;
	}

	return false;
}

//===============================
// コンストラクタ
//===============================
CAABBAABBCollision::CAABBAABBCollision()
{
}
//===============================
// デストラクタ
//===============================
CAABBAABBCollision::~CAABBAABBCollision()
{
	// 無し
}

//===============================
// 球と球のあたり判定
//===============================
bool CAABBAABBCollision::Collision(CAABBCollider* me, CAABBCollider* other)
{
	// ポインタ
	CAABBCollider* pMe = me;
	CAABBCollider* pOther = other;

	// 位置取得
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// サイズ取得
	D3DXVECTOR3 fMeSize = pMe->GetSize();
	D3DXVECTOR3 fOtherSize = pOther->GetSize();

	// 中心点同士の距離
	D3DXVECTOR3 dist = mePos - otherPos;
	float fDist = D3DXVec3Length(&dist);

	// 半径の合計
	//float fRadSum = fMeRad + fOtherRad;

	//if (fDist < fRadSum)
	//{// 半径の合計をより距離が近い
	//	return true;
	//}

	return false;
}
