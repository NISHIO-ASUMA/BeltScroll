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
#include "collider.h"
#include "collision.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_pAABB = nullptr;
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
	pBlock->SetFilePass(FileName);
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(Scale);

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

	// AABB�R���C�_�[����
	m_pAABB = CAABBCollider::Create(GetPos(), GetPos(), GetSize());

	return S_OK;
}
//================================
// �I������
//================================
void CBlock::Uninit(void)
{
	// �|�C���^�̔j��
	if (m_pAABB)
	{
		delete m_pAABB;
		m_pAABB = nullptr;
	}

	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CBlock::Update(void)
{
	// ���W�擾
	D3DXVECTOR3 pos = GetPos();

	// �R���C�_�[���W�X�V
	m_pAABB->SetPos(pos);

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
// ��`�̓����蔻��
//================================
bool CBlock::Collision(CAABBCollider* pOther, D3DXVECTOR3* pOutPos)
{
	// ��`�̓����蔻���Ԃ�
	return CAABBAABBCollision::CollisionT(m_pAABB,pOther, pOutPos);
}