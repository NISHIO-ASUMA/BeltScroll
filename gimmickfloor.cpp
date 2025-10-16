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
#include "gamemanager.h"
#include "trushSim.h"
#include "game.h"
#include "collider.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CGimmickFloor::CGimmickFloor(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_fMoveCnt = 0.0f;
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

	m_pCollider = CSphereCollider::Create(GetPos(), 100.0f);

	return S_OK;
}
//================================
// �I������
//================================
void CGimmickFloor::Uninit(void)
{

	delete m_pCollider;
	m_pCollider = nullptr;

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
	
	CGameManager* pGameManager = CGame::GetGameManager();
	CTrushSim* pTrush = pGameManager->GetTrush();

	if (!pTrush->Collision(m_pCollider))
	{
		// �T�C����Z�����ɓ�����
		pos.z += sinf(m_fMoveCnt)*10.0f;
	}

	m_pCollider->SetPos(pos);
	// ���f
	CObjectX::SetPos(pos);
	
	// �J�E���g
	m_fMoveCnt += COUNTSPEED;
}