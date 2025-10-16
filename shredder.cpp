//=====================================
//
// �V�����b�_�[���� [ shredder.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "shredder.h"

//===============================
// �R���X�g���N�^
//===============================
CShredder::CShredder(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CShredder::~CShredder()
{
	// ����
}
//===============================
// ��������
//===============================
CShredder* CShredder::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CShredder* pShredder = new CShredder;
	if (pShredder == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pShredder->SetPos(pos);
	pShredder->SetRot(VECTOR3_NULL);
	pShredder->SetFilePass("data/MODEL/STAGEOBJ/Shredder.x");

	// ���������s��
	if (FAILED(pShredder->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pShredder;
}
//===============================
// ����������
//===============================
HRESULT CShredder::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredder::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//===============================
// �X�V����
//===============================
void CShredder::Update(void)
{
	// ����
}
//===============================
// �`�揈��
//===============================
void CShredder::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
