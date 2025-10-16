//=====================================
//
// �R���W�������� [ collision.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _COLLISION_H_ // ���̃}�N����`������ĂȂ�������
#define _COLLISION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*************************
// �O���錾
//*************************
class CSphereCollider;
class CAABBCollider;


//*************************
// �R���W�����N���X���`
//*************************
class CCollision
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCollision();
	~CCollision();

	// �����o�֐�
private:
};

//**************************************************
// ���Ƌ��̂����蔻��N���X���`
//**************************************************
class CSphereSphereCollision:public CCollision
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSphereSphereCollision();
	~CSphereSphereCollision();

	// �����o�֐�
	static bool Collision(CSphereCollider*me, CSphereCollider*other);
private:
};


//**************************************************
// ��`�Ƌ�`�̂����蔻��N���X���`
//**************************************************
class CAABBAABBCollision :public CCollision
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CAABBAABBCollision();
	~CAABBAABBCollision();

	// �����o�֐�
	static bool Collision(CAABBCollider* me, CAABBCollider* other);
private:
};

#endif