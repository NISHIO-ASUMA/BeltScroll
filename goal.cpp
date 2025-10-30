//===================================
//
// �S�[���n�_���� [ goal.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�K�[�h
//******************************
#include "goal.h"

//====================================
// �R���X�g���N�^
//====================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority) , m_DestPos(VECTOR3_NULL)
{
	// �l�̃N���A
}
//====================================
// �f�X�g���N�^
//====================================
CGoal::~CGoal()
{
	// ����
}
//====================================
// ��������
//====================================
CGoal* CGoal::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CGoal* pGoal = new CGoal;
	if (pGoal == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pGoal->SetPos(pos);
	pGoal->SetRot(VECTOR3_NULL);
	pGoal->SetFilePass("data/MODEL/STAGEOBJ/Goal.x");

	// ���������s��
	if (FAILED(pGoal->Init())) 	return nullptr;

	return pGoal;
}
//====================================
// ����������
//====================================
HRESULT CGoal::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	// ���W���i�[����
	m_DestPos = GetPos();

	return S_OK;
}
//====================================
// �I������
//====================================
void CGoal::Uninit(void)
{
	// �e�N���X�̔j��
	CObjectX::Uninit();
}
//====================================
// �X�V����
//====================================
void CGoal::Update(void)
{
	// �e�N���X�̍X�V
	CObjectX::Update();
}
//====================================
// �`�揈��
//====================================
void CGoal::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
//====================================
// �`�F�b�N����
//====================================
bool CGoal::CheckPos(D3DXVECTOR3 pos)
{
	// �����v�Z
	D3DXVECTOR3 diffpos = m_DestPos - pos;

	// �����v�Z
	float fLength = D3DXVec3Length(&diffpos);

	// �͈͓��̍��W�ɓ����Ă�����
	if (fLength < 120.0f)
	{
		return true;
	}

	// �͈͊O�Ȃ�
	return false;
}