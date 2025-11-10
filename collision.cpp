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
bool CAABBAABBCollision::Collision(CAABBCollider* me, CAABBCollider* other, D3DXVECTOR3* pOutPos)
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
				// 押し出す座標を計算
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
//=================================
// 矩形と矩形の当たり判定 ( Asuma )
//=================================
bool CAABBAABBCollision::CollisionT(CAABBCollider* me, CAABBCollider* other, D3DXVECTOR3* pOutPos)
{
	//===========================
	// コライダーポインタ情報
	//===========================
	CAABBCollider* pMyCollider = me;
	CAABBCollider* pOtherCollider = other;

	//===========================
	// 自分と相手の座標を取得
	//===========================
	D3DXVECTOR3 MyPos = pMyCollider->GetPos();
	D3DXVECTOR3 OtherPos = pOtherCollider->GetPos();

	//===========================
	// コライダーサイズを取得
	//===========================
	D3DXVECTOR3 MySize = pMyCollider->GetSize();
	D3DXVECTOR3 OtherSize = pOtherCollider->GetSize();

	//================================
	// 自分と相手の半分のサイズを取得
	//================================
	D3DXVECTOR3 MyHalfSize = MySize * 0.5f;
	D3DXVECTOR3 OtherHalfSize = OtherSize * 0.5f;

	//===============================
	// 最大最小座標を計算する
	//===============================
	D3DXVECTOR3 MyPosMax = MyPos + MyHalfSize;
	D3DXVECTOR3 MyPosMin = MyPos - MyHalfSize;
	D3DXVECTOR3 OtherPosMax = OtherPos + OtherHalfSize;
	D3DXVECTOR3 OtherPosMin = OtherPos - OtherHalfSize;

	//===========================
	// 過去の座標を取得
	//===========================
	D3DXVECTOR3 MyPosOldMin = pMyCollider->GetPosOld() - MyHalfSize;
	D3DXVECTOR3 MyPosOldMax = pMyCollider->GetPosOld() + MyHalfSize;
	D3DXVECTOR3 OtherPosOldMin = pOtherCollider->GetPosOld() - OtherHalfSize;
	D3DXVECTOR3 OtherPosOldMax = pOtherCollider->GetPosOld() + OtherHalfSize;

	// 高さの範囲内に入って無かったら判定をしない
	const bool isHitRangeY = MyPosOldMin.y <= OtherPosOldMax.y && MyPosOldMax.y >= OtherPosOldMin.y;
	if (!isHitRangeY) return false;

	//==============================
	// z軸の範囲内に入っているとき
	//==============================
	if (OtherPosMin.z < MyPosMax.z && OtherPosMax.z > MyPosOldMin.z)
	{
		if (MyPosOldMax.x <= OtherPosMin.x && MyPosMax.x > OtherPosMin.x)
		{// 左からめり込む

			// 左側への押し出し座標を計算
			pOutPos->x = OtherPosMin.x - MyHalfSize.x - 0.1f;
			return true;
		}
		else if (MyPosOldMin.x >= OtherPosOldMax.x && MyPosMin.x <= OtherPosMax.x)
		{// 右からめり込む

			// 右側への押し出し座標を計算
			pOutPos->x = OtherPosMax.x + MyHalfSize.x + 0.1f;
			return true;
		}
	}

	//==============================
	// x軸の範囲内に入っているとき
	//==============================
	if (MyPosOldMin.x < OtherPosMax.x && MyPosMax.x > OtherPosMin.x)
	{
		if (MyPosOldMax.z < OtherPosMin.z && MyPosMax.z > OtherPosMin.z)
		{// 手前からめり込む

			// 手前への押しだし座標を計算
			pOutPos->z = OtherPosMin.z - MyHalfSize.z - 0.1f;
			return true;
		}
		else if (MyPosOldMin.z > OtherPosMax.z && MyPosMin.z < OtherPosMax.z)
		{// 奥から手前にめり込む

			// 奥側に押し出す座標を計算する
			pOutPos->z = OtherPosMax.z + MyHalfSize.z + 0.1f;
			return true;
		}
	}

	// 未ヒット時
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

	// 定数
	float MeMinX = mePos.x - fHalfMeSize.x - fOtherRadius;
	float MeMinY = mePos.y - fHalfMeSize.y - fOtherRadius;
	float MeMinZ = mePos.z - fHalfMeSize.z - fOtherRadius;

	float MeMaxX = mePos.x + fHalfMeSize.x + fOtherRadius;
	float MeMaxY = mePos.y + fHalfMeSize.y + fOtherRadius;
	float MeMaxZ = mePos.z + fHalfMeSize.z + fOtherRadius;


	if (otherPos.x < MeMaxX && otherPos.x > MeMinX)
	{// X軸の判定
		return true;
	}
	else if (otherPos.y<MeMaxY && otherPos.y > MeMinY)
	{// Y軸の判定
		return true;
	}
	else if (otherPos.z<MeMaxZ && otherPos.z > MeMinZ)
	{// Z軸の判定
		return true;
	}

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{// 八角とのあたり判定
		D3DXVECTOR3 Dist = mePosCornor[nCnt] - otherPos;

		float fDist= D3DXVec3Length(&Dist);

		if (fDist < fOtherRadius)
		{
			return true;
		}
	}

	return false;
}
//======================================
// 球と矩形の当たり判定関数 ( Asuma )
//======================================
bool CAABBSphereCollision::CollisionT(CAABBCollider* me, CSphereCollider* other)
{
	// 位置とサイズ
	D3DXVECTOR3 mePos = me->GetPos();
	D3DXVECTOR3 meSize = me->GetSize() * 0.5f;
	D3DXVECTOR3 spherePos = other->GetPos();
	float sphereRadius = other->GetRadius();

	// AABBの最小最大座標
	D3DXVECTOR3 boxMin = mePos - meSize;
	D3DXVECTOR3 boxMax = mePos + meSize;

	// 球の中心からAABB上の最近点を求める
	D3DXVECTOR3 closest;
	closest.x = max(boxMin.x, min(spherePos.x, boxMax.x));
	closest.y = max(boxMin.y, min(spherePos.y, boxMax.y));
	closest.z = max(boxMin.z, min(spherePos.z, boxMax.z));

	// 最近点と球の中心の距離を求める
	D3DXVECTOR3 diff = spherePos - closest;
	float dist = D3DXVec3Length(&diff);

	if (dist <= sphereRadius)
	{
		return true;
	}

	return false;
}