//====================================
//
// �R���W�������� [ collision.cpp ]
// Author: Sasaki Soichiro 
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "collision.h"
#include "collider.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CCollision::CCollision()
{
}
//===============================
// �f�X�g���N�^
//===============================
CCollision::~CCollision()
{
	// ����
}



//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CSphereSphereCollision::CSphereSphereCollision()
{
}
//===============================
// �f�X�g���N�^
//===============================
CSphereSphereCollision::~CSphereSphereCollision()
{
	// ����
}

//===============================
// ���Ƌ��̂����蔻��
//===============================
bool CSphereSphereCollision::Collision(CSphereCollider* me, CSphereCollider* other)
{
	// �|�C���^
	CSphereCollider* pMe = me;
	CSphereCollider* pOther = other;

	// �ʒu�擾
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// ���a�擾
	float fMeRad = pMe->GetRadius();
	float fOtherRad = pOther->GetRadius();

	// ���S�_���m�̋���
	D3DXVECTOR3 dist = mePos - otherPos;
	float fDist = D3DXVec3Length(&dist);

	// ���a�̍��v
	float fRadSum = fMeRad + fOtherRad;

	if (fDist < fRadSum)
	{// ���a�̍��v����苗�����߂�
		return true;
	}

	return false;
}

