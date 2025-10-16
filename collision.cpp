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
// �R���X�g���N�^
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
// �R���X�g���N�^
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

//===============================
// �R���X�g���N�^
//===============================
CAABBAABBCollision::CAABBAABBCollision()
{
}
//===============================
// �f�X�g���N�^
//===============================
CAABBAABBCollision::~CAABBAABBCollision()
{
	// ����
}

//===============================
// ���Ƌ��̂����蔻��
//===============================
bool CAABBAABBCollision::Collision(CAABBCollider* me, CAABBCollider* other)
{
	// �|�C���^
	CAABBCollider* pMe = me;
	CAABBCollider* pOther = other;

	// �ʒu�擾
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 fMeSize = pMe->GetSize();
	D3DXVECTOR3 fOtherSize = pOther->GetSize();

	// ���S�_���m�̋���
	D3DXVECTOR3 dist = mePos - otherPos;
	float fDist = D3DXVec3Length(&dist);

	// ���a�̍��v
	//float fRadSum = fMeRad + fOtherRad;

	//if (fDist < fRadSum)
	//{// ���a�̍��v����苗�����߂�
	//	return true;
	//}

	return false;
}
