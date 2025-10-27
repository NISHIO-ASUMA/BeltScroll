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


//===============================
// �R���X�g���N�^
//===============================
CAABBSphereCollision::CAABBSphereCollision()
{
}
//===============================
// �f�X�g���N�^
//===============================
CAABBSphereCollision::~CAABBSphereCollision()
{
	// ����
}

//===============================
// ��`�Ƌ��̓����蔻��
//===============================
bool CAABBSphereCollision::Collision(CAABBCollider* me, CSphereCollider* other)
{
	// �|�C���^
	CAABBCollider* pMe = me;
	CSphereCollider* pOther = other;

	// �ʒu�擾
	D3DXVECTOR3 mePos = pMe->GetPos();
	D3DXVECTOR3 otherPos = pOther->GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 fMeSize = pMe->GetSize();
	float fOtherRadius = pOther->GetRadius();

	// �����̃T�C�Y
	D3DXVECTOR3 fHalfMeSize = fMeSize * 0.5f;

	// �S�Ă̊p�Ƌ��̔�������邽��
	D3DXVECTOR3 mePosCornor[8];

	mePosCornor[0] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[1] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[2] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[3] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z + fHalfMeSize.z);
	mePosCornor[4] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[5] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y + fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[6] = D3DXVECTOR3(mePos.x + fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z - fHalfMeSize.z);
	mePosCornor[7] = D3DXVECTOR3(mePos.x - fHalfMeSize.x, mePos.y - fHalfMeSize.y, mePos.z - fHalfMeSize.z);

	if (otherPos.x<mePos.x + fHalfMeSize.x + fOtherRadius || otherPos.x > mePos.x - fHalfMeSize.x- fOtherRadius)
	{
		return true;
	}
	else if (otherPos.y<mePos.y + fHalfMeSize.y + fOtherRadius || otherPos.y > mePos.y - fHalfMeSize.y - fOtherRadius)
	{
		return true;
	}
	else if (otherPos.z<mePos.z + fHalfMeSize.z + fOtherRadius || otherPos.z > mePos.z - fHalfMeSize.z - fOtherRadius)
	{
		return true;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		D3DXVECTOR3 Dist = mePosCornor[nCnt] - otherPos;

		float fDist= D3DXVec3Length(&Dist);

		if (fDist < fOtherRadius)
		{
			return true;
		}
	}

	return false;
}
