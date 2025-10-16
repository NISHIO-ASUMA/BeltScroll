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

	pSphereCollider->SetPos(pos);
	pSphereCollider->SetRadius(fRadius);

	// �������ꂽ�C���X�^���X��Ԃ�
	return pSphereCollider;

}