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
// ��`�Ƌ�`�̓����蔻��
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

	// �����̃T�C�Y
	D3DXVECTOR3 fHalfMeSize = fMeSize * 0.5f;
	D3DXVECTOR3 fHalfOtherSize = fOtherSize * 0.5f;

	if (mePos.y - fHalfMeSize.y< otherPos.y + fHalfOtherSize.y && mePos.y + fHalfMeSize.y > otherPos.y - fHalfOtherSize.y)
	{// Y�����d�Ȃ��Ă���Ƃ�
		if (mePos.x - fHalfMeSize.x< otherPos.x + fHalfOtherSize.x && mePos.x + fHalfMeSize.x > otherPos.x - fHalfOtherSize.x)
		{// X�����d�Ȃ��Ă���Ƃ�

			// Z���̔���
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
		{// Z�����d�Ȃ��Ă���Ƃ�

			// X���̔���
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
	{// X����Z�����d�Ȃ��Ă���Ƃ�
		if (mePos.y - fHalfMeSize.y < otherPos.y + fHalfOtherSize.y)
		{// �ォ��
			return true;
		}
		else if (mePos.y + fHalfMeSize.y > otherPos.y - fHalfOtherSize.y)
		{// ������
			return true;
		}
	}

	return false;
}
