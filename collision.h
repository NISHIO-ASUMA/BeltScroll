//=====================================
//
// コリジョン処理 [ collision.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _COLLISION_H_ // このマクロ定義がされてなかったら
#define _COLLISION_H_ // 2重インクルード防止のマクロ定義

//*************************
// 前方宣言
//*************************
class CSphereCollider;
class CAABBCollider;


//*************************
// コリジョンクラスを定義
//*************************
class CCollision
{
public:
	// コンストラクタ・デストラクタ
	CCollision();
	~CCollision();

	// メンバ関数
private:
};

//**************************************************
// 球と球のあたり判定クラスを定義
//**************************************************
class CSphereSphereCollision:public CCollision
{
public:
	// コンストラクタ・デストラクタ
	CSphereSphereCollision();
	~CSphereSphereCollision();

	// メンバ関数
	static bool Collision(CSphereCollider*me, CSphereCollider*other);
private:
};


//**************************************************
// 矩形と矩形のあたり判定クラスを定義
//**************************************************
class CAABBAABBCollision :public CCollision
{
public:
	// コンストラクタ・デストラクタ
	CAABBAABBCollision();
	~CAABBAABBCollision();

	// メンバ関数
	static bool Collision(CAABBCollider* me, CAABBCollider* other);
private:
};

#endif