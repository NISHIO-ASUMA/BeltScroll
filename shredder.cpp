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
#include "game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "shreddermanager.h"
#include "collider.h"
#include "collision.h"

//===============================
// �R���X�g���N�^
//===============================
CShredder::CShredder(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_pAABB = nullptr;
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
CShredder* CShredder::Create(D3DXVECTOR3 pos,int nType)
{
	// �C���X�^���X����
	CShredder* pShredder = new CShredder;
	if (pShredder == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pShredder->SetPos(pos);
	pShredder->SetRot(VECTOR3_NULL);
	pShredder->m_nType = nType;

	switch (nType)
	{
	case CShredderManager::TYPE_RED:
		pShredder->SetFilePass("data/MODEL/STAGEOBJ/Red.x");
		break;
	case CShredderManager::TYPE_GREEN:
		pShredder->SetFilePass("data/MODEL/STAGEOBJ/Green.x");
		break;
	}

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

	// ��`�R���C�_�[����
	m_pAABB = CAABBCollider::Create(GetPos(), GetSize());

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredder::Uninit(void)
{
	// �j��
	delete m_pAABB;
	m_pAABB = nullptr;

	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//===============================
// �X�V����
//===============================
void CShredder::Update(void)
{
	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	CGameManager* pGameManager = CGame::GetGameManager();
	CPlayer* pPlayer = pGameManager->GetPlayer();
	D3DXVECTOR3 pPos = pPlayer->GetPos();
	D3DXVECTOR3 pPosOld = pPlayer->GetOldPos();

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera->GetMove())
	{
		pos.x += pPos.x - pPosOld.x;
		SetPos(pos);
	}

	// ���W�X�V
	m_pAABB->SetPos(pos);
}
//===============================
// �`�揈��
//===============================
void CShredder::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}

//===============================
// Z�������𓮂��������Ƃ�
//===============================
void CShredder::SetPosZ(float posZ)
{
	D3DXVECTOR3 pos = GetPos();
	pos.z = posZ;
	SetPos(pos);
}