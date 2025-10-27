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
// 矩形と矩形の当たり判定
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

	// 半分のサイズ
	D3DXVECTOR3 fHalfMeSize = fMeSize * 0.5f;
	D3DXVECTOR3 fHalfOtherSize = fOtherSize * 0.5f;

	if (mePos.y - fHalfMeSize.y< otherPos.y + fHalfOtherSize.y && mePos.y + fHalfMeSize.y > otherPos.y - fHalfOtherSize.y)
	{// Y軸が重なっているとき
		if (mePos.x - fHalfMeSize.x< otherPos.x + fHalfOtherSize.x && mePos.x + fHalfMeSize.x > otherPos.x - fHalfOtherSize.x)
		{// X軸が重なっているとき

			// Z軸の判定
			if (mePos.z - fHalfMeSize.z < otherPos.z + fHalfOtherSize.z)
			{
				return true;
			}
			else if (mePos.z + fHalfMeSize.z > otherPos.z - fHalfOtherSize.z)
			{
				return true;
			}

		}
		else if (mePos.z - fHalfMeSize.z< otherPos.z + fHalfOtherSize.z && mePos.z + fHalfMeSize.z > otherPos.z - fHalfOtherSize.z)
		{// Z軸が重なっているとき

			// X軸の判定
			if (mePos.x - fHalfMeSize.x < otherPos.x + fHalfOtherSize.x)
			{
				return true;
			}
			else if (mePos.x + fHalfMeSize.x > otherPos.x - fHalfOtherSize.x)
			{
				return true;
			}

		}
	}
	if (mePos.x - fHalfMeSize.x< otherPos.x + fHalfOtherSize.x && mePos.x + fHalfMeSize.x > otherPos.x - fHalfOtherSize.x &&
		mePos.z - fHalfMeSize.z < otherPos.z + fHalfOtherSize.z && mePos.z + fHalfMeSize.z > otherPos.z - fHalfOtherSize.z)
	{// X軸とZ軸が重なっているとき
		if (mePos.y - fHalfMeSize.y < otherPos.y + fHalfOtherSize.y)
		{// 上から
			return true;
		}
		else if (mePos.y + fHalfMeSize.y > otherPos.y - fHalfOtherSize.y)
		{// 下から
			return true;
		}
	}

	return false;
}


//===============================
// コンストラクタ
//===============================
CAABBSphereCollision::CAABBSphereCollision()
{
}
//===============================
// デストラクタ
//===============================
CAABBSphereCollision::~CAABBSphereCollision()
{
	// 無し
}

//===============================
// 矩形と球の当たり判定
//===============================
bool CAABBSphereCollision::Collision(CAABBCollider* me, CSphereCollider* other)
{
	// ポインタ
	CAABBCollider* pMe = me;
	CSphereCollider* pOther = other;

	// 位置取得
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// サイズ取得
	D3DXVECTOR3 fMeSize = pMe->GetSize();
	float fOtherRadius = pOther->GetRadius();

	// 半分のサイズ
	D3DXVECTOR3 fHalfMeSize = fMeSize * 0.5f;

	// 全ての角と球の判定をするため
	D3DXVECTOR3 mePosCornor[8];

	mePosCornor[0] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[1] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[2] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[3] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[4] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[5] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[6] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[7] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z - fHalfMeSize.z);

	if (otherPos.x<mePos.x + fHalfMeSize.x + fOtherRadius || otherPos.x > mePos.x - fHalfMeSize.x- fOtherRadius)
	{
		return true;
	}
	else if (otherPos.y<mePos.y + fHalfMeSize.y + fOtherRadius || otherPos.y > mePos.y - fHalfMeSize.y - fOtherRadius)
	{
		return true;
	}
	else if (otherPos.z<mePos.z + fHalfMeSize.z + fOtherRadius || otherPos.z > mePos.z - fHalfMeSize.z - fOtherRadius)
	{
		return true;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		D3DXVECTOR3 Dist = mePosCornor[nCnt] - otherPos;

		float fDist= D3DXVec3Length(&Dist);

		if (fDist < fOtherRadius)
		{
			return true;
		}
	}

	return false;
}
