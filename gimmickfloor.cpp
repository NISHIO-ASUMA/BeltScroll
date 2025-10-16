//=====================================
//
// ���������� [ gimmickfloor.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gimmickfloor.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CGimmickFloor::CGimmickFloor(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//================================
// �f�X�g���N�^
//================================
CGimmickFloor::~CGimmickFloor()
{
	// ����
}
//================================
// ��������
//================================
CGimmickFloor* CGimmickFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// �C���X�^���X����
	CGimmickFloor* pBlock = new CGimmickFloor;
	if (pBlock == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(Scale);
	pBlock->SetFilePass(FileName);

	// ���������s��
	if (FAILED(pBlock->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pBlock;
}
//================================
// ����������
//================================
HRESULT CGimmickFloor::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	return S_OK;
}
//================================
// �I������
//================================
void CGimmickFloor::Uninit(void)
{
	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CGimmickFloor::Update(void)
{
	// ������
	Move();

	// �e�N���X�̍X�V
	CObjectX::Update();
}
//================================
// �`�揈��
//================================
void CGimmickFloor::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}

//================================
// ����������
//================================
void CGimmickFloor::Move(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	// �T�C����Z�����ɓ�����
	pos.z = sinf(m_fMoveCnt);

	// ���f
	CObjectX::SetPos(pos);
	
	// �J�E���g
	m_fMoveCnt = COUNTSPEED;
}

//================================
// �����蔻��
//================================
bool CGimmickFloor::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// ������Ȃ���
	return false;
}