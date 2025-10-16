//====================================
//
// コリジョン処理 [ collision.cpp ]
// Author: Sasaki Soichiro 
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "collider.h"

//===============================
// コンストラクタ
//===============================
CCollider::CCollider()
{
	m_pos = VECTOR3_NULL;
}
//===============================
// デストラクタ
//===============================
CCollider::~CCollider()
{
	// 無し
}


//===============================
// コンストラクタ
//===============================
CSphereCollider::CSphereCollider()
{
	m_fRadius = 0.0f;
}
//===============================
// デストラクタ
//===============================
CSphereCollider::~CSphereCollider()
{
	// 無し
}

//===============================
// インスタンス生成
//===============================
CSphereCollider* CSphereCollider::Create(D3DXVECTOR3 pos, float fRadius)
{
	// インスタンス生成
	CSphereCollider* pSphereCollider = new CSphereCollider;
	if (pSphereCollider == nullptr) return nullptr;

	pSphereCollider->SetPos(pos);
	pSphereCollider->SetRadius(fRadius);

	// 生成されたインスタンスを返す
	return pSphereCollider;

}