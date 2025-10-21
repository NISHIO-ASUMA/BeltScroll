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
	D3DXVECTOR3 pos = GetPos();

	CGameManager* pGameManager = CGame::GetGameManager();
	CPlayer* pPlayer = pGameManager->GetPlayer();
	D3DXVECTOR3 pPos = pPlayer->GetPos();
	D3DXVECTOR3 pPosOld = pPlayer->GetOldPos();

	if (pPosOld.x < pPos.x)
	{
		pos.x += pPos.x - pPosOld.x;
		SetPos(pos);
	}

}
//===============================
// �`�揈��
//===============================
void CShredder::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
