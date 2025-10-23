//=============================================
//
// �����v���C���[���� [ winplayer.h ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "winplayer.h"
#include "motion.h"
#include "model.h"
#include "manager.h"
#include "shadowS.h"

//================================
// �R���X�g���N�^
//================================
CWinPlayer::CWinPlayer(int nPriority) : CObject(nPriority),
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

}
//================================
// �f�X�g���N�^
//================================
CWinPlayer::~CWinPlayer()
{

}
//================================
// ��������
//================================
CWinPlayer* CWinPlayer::Create(D3DXVECTOR3 pos)
{
	CWinPlayer* winplayer = new CWinPlayer;
	if (winplayer == nullptr) return nullptr;

	winplayer->m_pos = pos;
	winplayer->m_rot = VECTOR3_NULL;
	winplayer->m_pFilename = "data/MOTION/Player/WinPlayer.txt";

	if (FAILED(winplayer->Init()))
	return nullptr;

	return winplayer;
}
//================================
// ����������
//================================
HRESULT CWinPlayer::Init(void)
{
	// ���[�V�����ǂݍ���
	m_pMotion = CMotion::Load(m_pFilename, WIN_MODEL, m_apModel, WINMOTION_MAX);
	m_pMotion->SetMotionNum(WINMOTION_MAX);

	// �X�e���V���V���h�E����
	m_pShadowS = CShadowS::Create
	(
		m_pos,
		m_rot
	);

	// �������[�V�����Z�b�g
	m_pMotion->SetMotion(WINMOTION_ACTION);

	return S_OK;
}
//================================
// �I������
//================================
void CWinPlayer::Uninit(void)
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
//================================
// �X�V����
//================================
void CWinPlayer::Update(void)
{
	// �X�e���V���V���h�E������
	if (m_pShadowS)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadowS->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z));
		m_pShadowS->SetRot(m_rot);
	}

	// ���[�V�����X�V
	m_pMotion->Update(m_apModel, WIN_MODEL);
}
//================================
// �`�揈��
//================================
void CWinPlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < WIN_MODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}