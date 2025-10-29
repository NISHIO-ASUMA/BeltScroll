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
bool CAABBAABBCollision::Collision(CAABBCollider* me, CAABBCollider* other, D3DXVECTOR3* pOutPos)
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
				// �����o�����W���v�Z
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
//=================================
// ��`�Ƌ�`�̓����蔻�� ( Asuma )
//=================================
bool CAABBAABBCollision::CollisionT(CAABBCollider* me, CAABBCollider* other, D3DXVECTOR3* pOutPos)
{
	//===========================
	// �R���C�_�[�|�C���^���
	//===========================
	CAABBCollider* pMyCollider = me;
	CAABBCollider* pOtherCollider = other;

	//===========================
	// �����Ƒ���̍��W���擾
	//===========================
	D3DXVECTOR3 MyPos = pMyCollider->GetPos();
	D3DXVECTOR3 OtherPos = pOtherCollider->GetPos();

	//===========================
	// �R���C�_�[�T�C�Y���擾
	//===========================
	D3DXVECTOR3 MySize = pMyCollider->GetSize();
	D3DXVECTOR3 OtherSize = pOtherCollider->GetSize();

	//================================
	// �����Ƒ���̔����̃T�C�Y���擾
	//================================
	D3DXVECTOR3 MyHalfSize = MySize * 0.5f;
	D3DXVECTOR3 OtherHalfSize = OtherSize * 0.5f;

	//===============================
	// �ő�ŏ����W���v�Z����
	//===============================
	D3DXVECTOR3 MyPosMax = MyPos + MyHalfSize;
	D3DXVECTOR3 MyPosMin = MyPos - MyHalfSize;
	D3DXVECTOR3 OtherPosMax = OtherPos + OtherHalfSize;
	D3DXVECTOR3 OtherPosMin = OtherPos - OtherHalfSize;

	//===========================
	// �ߋ��̍��W���擾
	//===========================
	D3DXVECTOR3 MyPosOldMin = pMyCollider->GetPosOld() - MyHalfSize;
	D3DXVECTOR3 MyPosOldMax = pMyCollider->GetPosOld() + MyHalfSize;
	D3DXVECTOR3 OtherPosOldMin = pOtherCollider->GetPosOld() - OtherHalfSize;
	D3DXVECTOR3 OtherPosOldMax = pOtherCollider->GetPosOld() + OtherHalfSize;

	// �����͈͓̔��ɓ����Ė��������画������Ȃ�
	const bool isHitRangeY = MyPosOldMin.y <= OtherPosOldMax.y && MyPosOldMax.y >= OtherPosOldMin.y;
	if (!isHitRangeY) return false;

	//==============================
	// z���͈͓̔��ɓ����Ă���Ƃ�
	//==============================
	if (OtherPosMin.z < MyPosMax.z && OtherPosMax.z > MyPosOldMin.z)
	{
		if (MyPosOldMax.x <= OtherPosMin.x && MyPosMax.x > OtherPosMin.x)
		{// ������߂荞��

			// �����ւ̉����o�����W���v�Z
			pOutPos->x = OtherPosMin.x - MyHalfSize.x - 0.1f;
			return true;
		}
		else if (MyPosOldMin.x >= OtherPosMax.x && MyPosMin.x < OtherPosMax.x)
		{// �E����߂荞��

			// �E���ւ̉����o�����W���v�Z
			pOutPos->x = OtherPosMax.x + MyHalfSize.x + 0.1f;
			return true;
		}
	}

	//==============================
	// x���͈͓̔��ɓ����Ă���Ƃ�
	//==============================
	if (MyPosOldMin.x < OtherPosMax.x && MyPosMax.x > OtherPosMin.x)
	{
		if (MyPosOldMax.z < OtherPosMin.z && MyPosMax.z > OtherPosMin.z)
		{// ��O����߂荞��

			// ��O�ւ̉����������W���v�Z
			pOutPos->z = OtherPosMin.z - MyHalfSize.z - 0.1f;
			return true;
		}
		else if (MyPosOldMin.z > OtherPosMax.z && MyPosMin.z < OtherPosMax.z)
		{// �������O�ɂ߂荞��

			// �����ɉ����o�����W���v�Z����
			pOutPos->z = OtherPosMax.z + MyHalfSize.z + 0.1f;
			return true;
		}
	}

	// ���q�b�g��
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

	// �萔
	float MeMinX = mePos.x - fHalfMeSize.x - fOtherRadius;
	float MeMinY = mePos.y - fHalfMeSize.y - fOtherRadius;
	float MeMinZ = mePos.z - fHalfMeSize.z - fOtherRadius;

	float MeMaxX = mePos.x + fHalfMeSize.x + fOtherRadius;
	float MeMaxY = mePos.y + fHalfMeSize.y + fOtherRadius;
	float MeMaxZ = mePos.z + fHalfMeSize.z + fOtherRadius;


	if (otherPos.x < MeMaxX && otherPos.x > MeMinX)
	{// X���̔���
		return true;
	}
	else if (otherPos.y<MeMaxY && otherPos.y > MeMinY)
	{// Y���̔���
		return true;
	}
	else if (otherPos.z<MeMaxZ && otherPos.z > MeMinZ)
	{// Z���̔���
		return true;
	}

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{// ���p�Ƃ̂����蔻��
		D3DXVECTOR3 Dist = mePosCornor[nCnt] - otherPos;

		float fDist= D3DXVec3Length(&Dist);

		if (fDist < fOtherRadius)
		{
			return true;
		}
	}

	return false;
}
//======================================
// ���Ƌ�`�̓����蔻��֐� ( Asuma )
//======================================
bool CAABBSphereCollision::CollisionT(CAABBCollider* me, CSphereCollider* other)
{
	// �ʒu�ƃT�C�Y
	D3DXVECTOR3 mePos = me->GetPos();
	D3DXVECTOR3 meSize = me->GetSize() * 0.5f;
	D3DXVECTOR3 spherePos = other->GetPos();
	float sphereRadius = other->GetRadius();

	// AABB�̍ŏ��ő���W
	D3DXVECTOR3 boxMin = mePos - meSize;
	D3DXVECTOR3 boxMax = mePos + meSize;

	// ���̒��S����AABB��̍ŋߓ_�����߂�
	D3DXVECTOR3 closest;
	closest.x = max(boxMin.x, min(spherePos.x, boxMax.x));
	closest.y = max(boxMin.y, min(spherePos.y, boxMax.y));
	closest.z = max(boxMin.z, min(spherePos.z, boxMax.z));

	// �ŋߓ_�Ƌ��̒��S�̋��������߂�
	D3DXVECTOR3 diff = spherePos - closest;
	float dist = D3DXVec3Length(&diff);

	if (dist <= sphereRadius)
	{
		return true;
	}

	return false;
}