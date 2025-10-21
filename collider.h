//=====================================
//
// �R���C�_�[���� [ collider.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _COLLIDER_H_ // ���̃}�N����`������ĂȂ�������
#define _COLLIDER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*************************
// �R���C�_�[�N���X���`
//*************************
class CCollider
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCollider();
	~CCollider();

	// �����o�֐�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	D3DXVECTOR3 m_pos;	// �ʒu
};

//**************************************************
// �X�t�B�A�R���C�_�[�N���X���`
//**************************************************
class CSphereCollider :public CCollider
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSphereCollider();
	~CSphereCollider();

	// �����o�֐�
	static CSphereCollider* Create(D3DXVECTOR3 pos, float fRadius);

	void SetRadius(float radius) { m_fRadius = radius; }
	float GetRadius(void) { return m_fRadius; }
private:
	float m_fRadius;	// ���a
};

//**************************************************
// AABB�R���C�_�[�N���X���`
//**************************************************
class CAABBCollider :public CCollider
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CAABBCollider() { m_size = VECTOR3_NULL; }
	~CAABBCollider() {}

	// �����o�֐�
	static CAABBCollider* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	D3DXVECTOR3 m_size;	// �傫��
};


#endif