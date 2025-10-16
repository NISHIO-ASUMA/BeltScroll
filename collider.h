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
	float GetRadius(void) { return m_fRadius; }
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	float m_fRadius;	// ���a
};

#endif