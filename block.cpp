//=====================================
//
// �u���b�N���� [ block.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "block.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//================================
// �f�X�g���N�^
//================================
CBlock::~CBlock()
{
	// ����
}
//================================
// ��������
//================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// �C���X�^���X����
	CBlock* pBlock = new CBlock;
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
HRESULT CBlock::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	return S_OK;
}
//================================
// �I������
//================================
void CBlock::Uninit(void)
{
	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CBlock::Update(void)
{
	// �e�N���X�̍X�V
	CObjectX::Update();
}
//================================
// �`�揈��
//================================
void CBlock::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}
//================================
// �����蔻��
//================================
bool CBlock::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// ������Ȃ���
	return false;
}