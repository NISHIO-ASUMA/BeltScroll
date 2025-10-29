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
#include "model.h"

//===============================
// �R���X�g���N�^
//===============================
CShredder::CShredder(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_move = VECTOR3_NULL;
	m_nType = 0;
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
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
	pShredder->m_nType = nType;

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
	InitModel();
	// ���f���̌��������킹�邽��
	m_rot.y = D3DX_PI;

	// ��`�R���C�_�[����
	m_pAABB = CAABBCollider::Create(m_pos, m_pos,D3DXVECTOR3(100.0f,300.0f,500.0f));

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredder::Uninit(void)
{
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = nullptr;
	}

	// �j��
	delete m_pAABB;
	m_pAABB = nullptr;

	// ���g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CShredder::Update(void)
{
	CGameManager* pGameManager = CGame::GetGameManager();
	CPlayer* pPlayer = pGameManager->GetPlayer();
	D3DXVECTOR3 pPos = pPlayer->GetPos();
	D3DXVECTOR3 pPosOld = pPlayer->GetOldPos();

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera->GetMove())
	{
		m_pos.x += pPos.x - pPosOld.x;
		SetPos(m_pos);
	}

	// ���W�X�V
	m_pAABB->SetPos(m_pos);

	// ���f���̍X�V
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Update();
	}
	UpdateModel();

}
//===============================
// �`�揈��
//===============================
void CShredder::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

}

//===============================
// ���f���̏���������
//===============================
void CShredder::InitModel(void)
{
	// �^�C�v���ƂɈႤ����
	switch (m_nType)
	{
	case CShredderManager::TYPE_RED:
		m_apModel[0] = CModel::Create(VECTOR3_NULL, 
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
									"data/MODEL/STAGEOBJ/shredder(RED)frame.x");
		break;
	case CShredderManager::TYPE_GREEN:
		m_apModel[0] = CModel::Create(VECTOR3_NULL,
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
									"data/MODEL/STAGEOBJ/shredder(BRUE)frame.x");
		break;
	}


	// ���ʕ���
	m_apModel[1] = CModel::Create(VECTOR3_NULL,
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		"data/MODEL/STAGEOBJ/shredderblade.x");
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[1]->OffSetPos(VECTOR3_NULL);
}

//===============================
// �p�[�c�̓����X�V
//===============================
void CShredder::UpdateModel(void)
{
	// �n���񂷂����̏���
	D3DXVECTOR3 rot = m_apModel[1]->GetRot();

	rot.z += 0.5f;

	m_apModel[1]->SetRot(rot);
}

//===============================
// Z�������𓮂��������Ƃ�
//===============================
void CShredder::SetPosZ(float posZ)
{
	m_pos.z = posZ;
}

