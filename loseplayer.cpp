//=============================================
//
// �s�k�v���C���[���� [ loseplayer.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�t�@�C��
//**************************
#include "loseplayer.h"
#include "motion.h"
#include "model.h"
#include "shadowS.h"
#include "manager.h"

//==============================
// �R���X�g���N�^
//==============================
CLosePlayer::CLosePlayer(int nPriority) : CObject(nPriority),
m_apModel{},
m_pFilename{},
m_pMotion{},
m_pShadowS{},
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_rotDest(VECTOR3_NULL),
m_mtxworld{},
m_Scal(INITSCALE)
{
	// 
}
//==============================
// �f�X�g���N�^
//==============================
CLosePlayer::~CLosePlayer()
{
	// ����
}
//==============================
// ��������
//==============================
CLosePlayer* CLosePlayer::Create(D3DXVECTOR3 pos)
{
	CLosePlayer* loseplayer = new CLosePlayer;
	if (loseplayer == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	loseplayer->m_pos = pos;
	loseplayer->m_rot = VECTOR3_NULL;
	loseplayer->m_pFilename = "data/MOTION/Player/LosePlayer.txt";

	if (FAILED(loseplayer->Init()))
	{
		return nullptr;
	}

	return loseplayer;
}
//==============================
// ����������
//==============================
HRESULT CLosePlayer::Init(void)
{
	// ���[�V�����ǂݍ���
	m_pMotion = CMotion::Load(m_pFilename, LOSE_MODEL, m_apModel, LOSEMOTION_MAX);
	m_pMotion->SetMotionNum(LOSEMOTION_MAX);

	// �X�e���V���V���h�E����
	m_pShadowS = CShadowS::Create
	(
		m_pos,
		m_rot
	);

	// �������[�V�����Z�b�g
	m_pMotion->SetMotion(LOSEMOTION_ACTION);

	return S_OK;
}
//==============================
// �I������
//==============================
void CLosePlayer::Uninit(void)
{
	for (auto& model : m_apModel)
	{
		if (model != nullptr)
		{
			model->Uninit();

			delete model;

			model = nullptr;
		}
	}

	if (m_pMotion)
	{
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	CObject::Release();
}
//==============================
// �X�V����
//==============================
void CLosePlayer::Update(void)
{
	// �X�e���V���V���h�E������
	if (m_pShadowS)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadowS->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z));
		m_pShadowS->SetRot(m_rot);
	}

	// ���[�V�����X�V
	m_pMotion->Update(m_apModel, LOSE_MODEL);
}
//==============================
// �`�揈��
//==============================
void CLosePlayer::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, m_Scal.x, m_Scal.y, m_Scal.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < LOSE_MODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

}
