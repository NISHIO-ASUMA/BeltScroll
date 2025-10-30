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

	// 初期設定
	pSphereCollider->SetPos(pos);
	pSphereCollider->SetRadius(fRadius);

	// 生成されたインスタンスを返す
	return pSphereCollider;

}

//===============================
// インスタンス生成
//===============================
CAABBCollider* CAABBCollider::Create(D3DXVECTOR3 pos, D3DXVECTOR3 posOld,D3DXVECTOR3 size)
{
	// インスタンス生成
	CAABBCollider* pAABBCollider = new CAABBCollider;
	if (pAABBCollider == nullptr) return nullptr;

	// 初期設定
	pAABBCollider->SetPos(pos);
	pAABBCollider->SetOldPos(posOld);
	pAABBCollider->SetSize(size);

	// 生成されたインスタンスを返す
	return pAABBCollider;

}