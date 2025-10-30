//====================================
//
// �R���W�������� [ collision.cpp ]
// Author: Sasaki Soichiro 
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collider.h"

//===============================
// �R���X�g���N�^
//===============================
CCollider::CCollider()
{
	m_pos = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CCollider::~CCollider()
{
	// ����
}


//===============================
// �R���X�g���N�^
//===============================
CSphereCollider::CSphereCollider()
{
	m_fRadius = 0.0f;
}

//===============================
// �f�X�g���N�^
//===============================
CSphereCollider::~CSphereCollider()
{
	// ����
}

//===============================
// �C���X�^���X����
//===============================
CSphereCollider* CSphereCollider::Create(D3DXVECTOR3 pos, float fRadius)
{
	// �C���X�^���X����
	CSphereCollider* pSphereCollider = new CSphereCollider;
	if (pSphereCollider == nullptr) return nullptr;

	// �����ݒ�
	pSphereCollider->SetPos(pos);
	pSphereCollider->SetRadius(fRadius);

	// �������ꂽ�C���X�^���X��Ԃ�
	return pSphereCollider;

}

//===============================
// �C���X�^���X����
//===============================
CAABBCollider* CAABBCollider::Create(D3DXVECTOR3 pos, D3DXVECTOR3 posOld,D3DXVECTOR3 size)
{
	// �C���X�^���X����
	CAABBCollider* pAABBCollider = new CAABBCollider;
	if (pAABBCollider == nullptr) return nullptr;

	// �����ݒ�
	pAABBCollider->SetPos(pos);
	pAABBCollider->SetOldPos(posOld);
	pAABBCollider->SetSize(size);

	// �������ꂽ�C���X�^���X��Ԃ�
	return pAABBCollider;

}