//=====================================
//
// コライダー処理 [ collider.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _COLLIDER_H_ // このマクロ定義がされてなかったら
#define _COLLIDER_H_ // 2重インクルード防止のマクロ定義

//*************************
// コライダークラスを定義
//*************************
class CCollider
{
public:
	// コンストラクタ・デストラクタ
	CCollider();
	~CCollider();

	// メンバ関数
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	D3DXVECTOR3 m_pos;	// 位置
};

//**************************************************
// スフィアコライダークラスを定義
//**************************************************
class CSphereCollider :public CCollider
{
public:
	// コンストラクタ・デストラクタ
	CSphereCollider();
	~CSphereCollider();

	// メンバ関数
	static CSphereCollider* Create(D3DXVECTOR3 pos, float fRadius);

	void SetRadius(float radius) { m_fRadius = radius; }
	float GetRadius(void) { return m_fRadius; }
private:
	float m_fRadius;	// 半径
};

#endif