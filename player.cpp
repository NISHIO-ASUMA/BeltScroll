//=========================================
//
// �v���C���[���� [ player.cpp ]
// Author: Asuma Nishio
//
// TODO : �u�����[�̏��������
// 
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "state.h"
#include "sound.h"
#include "enemy.h"
#include "effect.h"
#include "particlepiler.h"

//**********************
// ���O���
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 5.0f;		 // 1�t���[���̈ړ���
	constexpr float JUMPVALUE = 19.0f;	 // �W�����v��
	constexpr float GRAVITY = 0.7f;		 // �d�͒l
	constexpr float HITRADIUS = 25.0f;	 // �����蔻��̔��a
	constexpr int   KeyRepeatCount = 15; // �L�[�̃��s�[�g�ő�J�E���g
};

//**********************
// �ÓI�����o�ϐ��錾
//**********************
bool CPlayer::m_isDeath = false;  // ���S�t���O

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_Scal = INITSCALE;
	m_State = NULL;
	m_nIdxTexture = NULL;
	m_rotDest = VECTOR3_NULL;
	m_nNumAll = NULL;
	m_type = NULL;
	m_posOld = VECTOR3_NULL;
	m_pFilename = {};
	m_nIdxPlayer = NULL;
	m_fAngle = NULL;
	m_fAvoidTime = NULL;

	// ���f���̃|�C���^�̃N���A
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// �N���X�|�C���^
	m_pMotion = nullptr;
	m_pShadowS = nullptr;
	m_pStateMachine = nullptr;

	// �t���O�����g
	m_isLanding = false;
	m_isJump = false;
	m_isAttack = false;
	m_isMoving = false;
}
//===============================
// �f�X�g���N�^
//===============================
CPlayer::~CPlayer()
{
	// ����
}
//===============================
// �v���C���[��������
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
{
	// �v���C���[�̃C���X�^���X����
	CPlayer* pPlayer = new CPlayer;

	// �C���X�^���X��nullptr��������
	if (pPlayer == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->m_pFilename = pFilename;

	// �v���C���[����������
	if (FAILED(pPlayer->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}
//===============================
// �v���C���[����������
//===============================
HRESULT CPlayer::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_PLAYER);

	// ���f����������
	m_nNumAll = MAX_MODEL;

	// ���[�V������ސ�����
	m_type = PLAYERMOTION_MAX;

	// �t���O��ݒ�
	m_isDeath = false;
	m_isJump = false;
	m_isLanding = false;
	m_isMoving = false;

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load(m_pFilename, MAX_MODEL, m_apModel,PLAYERMOTION_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(PLAYERMOTION_MAX);

	// �v���C���[���ʃ��f���t���O��ݒ�
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// nullptr����Ȃ�������
		if (m_apModel[nCnt] != nullptr)
		{
			// �t���O��ݒ肷��
			m_apModel[nCnt]->SetIsPlayer(true);
		}
	}
	
	// �X�e���V���V���h�E����
	m_pShadowS = CShadowS::Create
	(
		m_pos, 
		m_rot
	);
	

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = new CStateMachine;

	// ������Ԃ��Z�b�g
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �v���C���[�I������
//===============================
void CPlayer::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_apModel[nCnt] != nullptr)
		{
			// �I������
			m_apModel[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_apModel[nCnt];

			// nullptr�ɂ���
			m_apModel[nCnt] = nullptr;
		}
	}

	// nullptr�`�F�b�N
	if (m_pMotion != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pMotion;

		// nullptr�ɂ���
		m_pMotion = nullptr;
	}

	// nullptr�`�F�b�N
	if (m_pStateMachine != nullptr)
	{
		// �I������
		m_pStateMachine->OnExit();

		// �|�C���^�̔j��
		delete m_pStateMachine;

		// nullptr�ɂ���
		m_pStateMachine = nullptr;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}
//============================================================
// �v���C���[�X�V����
//============================================================
void CPlayer::Update(void)
{
	// ����ł�Ȃ珈�����Ȃ�
	if (m_isDeath) return;

	// ���̓f�o�C�X�̃|�C���^�擾
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;

	pInput = CManager::GetInputKeyboard();
	pJoyPad = CManager::GetJoyPad();

	//// nullptr����Ȃ��Ƃ�
	//if (m_pStateMachine != nullptr)
	//{
	//	// �X�e�[�g�X�V
	//	m_pStateMachine->Update();
	//}

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

#if 1
	//=====================
	// �ړ�����
	//=====================
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// A�L�[

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// ���΂ߏ�

			m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);

			// ���[�V�����ύX
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// �E�΂߉�

			m_move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);

			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else
		{// �P��
			m_move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);

			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// D�L�[��������

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// W�L�[��������
			m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);

			// �^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// S�L�[��������
			m_move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);

			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else
		{// D�L�[�̂݉�����
			m_move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);

			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// W�L�[��������

		m_move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y - (D3DX_PI);

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// �p�x�𐳋K��
		if (m_rot.y < -D3DX_PI)
		{// D3DX_PI��菬�����Ȃ�����
			m_rot.y += D3DX_PI * 2.0f;
		}

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// S�L�[��������

		m_move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y;

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE || !m_isJump)
		{
			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		}
	}

	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// ����]
		// �p�x
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// �E��]
		// �p�x
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// ���݂̊p�x
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;
#endif

	if (m_isJump == false)
	{// �W�����v���Ă��Ȃ��Ē��n���Ă��Ȃ��Ƃ�

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
		{
			m_isJump = true;
			m_isLanding = false;

			// �W�����v�L�[�������ꂽ
			m_move.y = PLAYERINFO::JUMPVALUE;
		}
	}

	// �W�����v���g���Ă���
	if (m_isJump)
	{
		// ���[�V�����ύX
		m_pMotion->SetMotion(PLAYERMOTION_JUMP);
	}

	// ���n���̏���
	if (m_isLanding)
	{
		// ���n���[�V�����ɕύX
		// m_pMotion->SetMotion(PLAYERMOTION_LANDING);

		// �W�����v�\��ԂɕύX
		m_isJump = false;

		//// ���[�V�����I�����@���� ��ނ����n���[�V����
		//if (m_pMotion->GetMotionType() == PLAYERMOTION_LANDING && m_pMotion->GetFinishMotion())
		//{
		//	m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		//}
	}

	// L�L�[�Ŕ͈͍U��
	if (CManager::GetInputKeyboard()->GetPress(DIK_L))
	{
		// �L������
		m_isAttack = true;

		// ������΂�
		EnemyBlow();

#ifdef _DEBUG
		// �p�[�e�B�N������
		CParticlePiler::Create(m_pos, D3DXCOLOR(0.12f, 1.0f, 0.03f, 1.0f), 20, 50.0f, 50.0f, 25, m_rot.y);
#endif // _DEBUG
	}

	// �d�͉��Z
	m_move.y -= PLAYERINFO::GRAVITY;

	// �ʒu�ۑ�
	m_posOld = m_pos;

	// �ʒu�X�V
	m_pos += m_move;

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * 0.75f;
	m_move.z += (0.0f - m_move.z) * 0.75f;

	// ���݂�y���W��0.0f�ȉ��̎�
	if (m_pos.y <= 0.0f)
	{
		// y���W��n�ʂ̍��W�ɐݒ�
		m_pos.y = 0.0f;

		// ���n�����L����
		m_isLanding = true;

		// �����ւ̈ړ��ʂ�0.0f�ɐݒ�
		m_move.y = 0.0f;
	}

	// �X�e���V���V���h�E������
	if (m_pShadowS)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadowS->SetPos(D3DXVECTOR3(m_pos.x,0.0f,m_pos.z));
		m_pShadowS->SetRot(m_rot); 
	}

	// ���[�V�����̑S�̍X�V
	m_pMotion->Update(m_apModel, MAX_MODEL); 
}
//===============================
// �v���C���[�`�揈��
//===============================
void CPlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	// ���ʕ`��
	CDebugproc::Print("�v���C���[�̍��W { %.2f,%.2f,%.2f }", m_pos.x, m_pos.y, m_pos.z);
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 120);

	// ���ʕ`��
	CDebugproc::Print("�v���C���[�̊p�x { %.2f,%.2f,%.2f }", m_rot.x, m_rot.y, m_rot.z);

	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 140);

	// ���[�V�����`��
	CDebugproc::Print("MAIN�v���C���[�̃��[�V���� { %d } ", GetNowMotion());

	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 160);
}
//=========================================
// ���f���̓��蕔���p�[�c�̎擾�֐�
//=========================================
CModel* CPlayer::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// �v���C���[�������Ă��郂�f���̐��̒�����T��
	for (int nModel = 0; nModel < MAX_MODEL; nModel++)
	{
		// ���f�������� ���� �擾���������ƈ�v���Ă�����
		if (m_apModel[nModel] && m_apModel[nModel]->GetPartType() == modelpart)
		{
			// �Y�����f����idx�ԍ��̃��f����Ԃ�
			return m_apModel[nModel];
		}
	}

	// �Y���Ȃ�
	return nullptr;
}

//=========================================
// �X�e�[�g�ύX
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// �������g����
	pNewState->SetOwner(this);

	// �X�e�[�g�ύX
	m_pStateMachine->ChangeState(pNewState);
}

//=========================================
// �U���X�V����
//=========================================
void CPlayer::UpdateAction(CInputKeyboard* pInputKeyboard,D3DXMATRIX pMtx,const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{

}

//=========================================
// �ړ��X�V����
//=========================================
void CPlayer::UpdateMove(CInputKeyboard* pInputKeyboard, CJoyPad* pPad)
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	//=====================
	// �ړ�����
	//=====================
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// A�L�[

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// ���΂ߏ�

			m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// �E�΂߉�

			m_move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);
		}
		else
		{// �P��
			m_move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);
		}

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// D�L�[��������

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// W�L�[��������
			m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// S�L�[��������
			m_move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);
		}
		else
		{// D�L�[�̂݉�����
			m_move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);
		}

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// W�L�[��������

		m_move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y - (D3DX_PI);

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// �p�x�𐳋K��
		if (m_rot.y < -D3DX_PI)
		{// D3DX_PI��菬�����Ȃ�����
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// S�L�[��������

		//�@�^�C�v�؂�ւ�
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		m_move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y;

		// �p�x�̐��K��
		if (m_rot.y > D3DX_PI)
		{// D3DX_PI���傫���Ȃ�����
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE)
		{
			//�@�^�C�v�؂�ւ�
			m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		}
	}

	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// ����]
		// �p�x
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// �E��]
		// �p�x
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// ���݂̊p�x
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;
}
//=========================================
// �W�����v�X�V����
//=========================================
void CPlayer::UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{

}
//=============================
// �R���W���������֐�
//=============================
void CPlayer::Collision(void)
{
#if 0

	// �_���[�W�����m�F
	if (GetStateMachine()->GetNowStateID() == CPlayerStateBase::ID_DAMAGE)
		return;

#endif
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// �����ꂩ�̈ړ��L�[����
	return (pKeyInput->GetPress(DIK_A) 
		|| pKeyInput->GetPress(DIK_D)
		|| pKeyInput->GetPress(DIK_S)
		|| pKeyInput->GetPress(DIK_W));
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// �����ꂩ�̈ړ��L�[����
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
//===============================
// �W�����v����֐�
//===============================
void CPlayer::StartJump(void)
{
	// �W�����v�L�[���� ���� �W�����v�t���O��false�̎�
	if (!m_isJump)
	{
		// �t���O��L����
		m_isJump = true;

		// �����n����ɕύX
		m_isLanding = false;

		// �㏸�l��ݒ�
		m_move.y = PLAYERINFO::JUMPVALUE;

		// �ړ��X�V
		AddMove();
	}
}
//===============================
// ���݂̃��[�V������ގ擾
//===============================
CPlayer::PLAYERMOTION CPlayer::GetNowMotion() const
{
	// null����Ȃ�������
	if (m_pMotion)
	{
		// ���ݔԍ���Ԃ�
		return static_cast<CPlayer::PLAYERMOTION>(m_pMotion->GetMotionType());
	}

	return PLAYERMOTION_NEUTRAL; // �f�t�H���g
}
//===============================
// �q�b�g����
//===============================
void CPlayer::HitDamage(int nDamage)
{
#if 0
	// �p�����[�^�[�擾
	int nHp = m_pParameter->GetHp();

	// �̗͂����炷
	nHp -= nDamage;

	// ���ݑ̗͂�0�ȉ�
	if (nHp <= NULL)
	{
		// ���ݑ̗͂��Z�b�g
		m_pParameter->SetHp(nHp);

		// ���S�t���O���Z�b�g
		m_isDeath = true;

		// ���[�V�����Z�b�g
		m_pMotion->SetMotion(PLAYERMOTION_DAMAGE, false, 0, false);

		return;
	}
	else
	{
		// ���ݑ̗͂��Z�b�g
		m_pParameter->SetHp(nHp);
	}

#endif
}
//=======================================
// �G������΂����� ( �͈͂��ǂ����邩 ) ��������,�W�ߕ�(�܂Ƃ߂ē����邽�߂�)
//=======================================
void CPlayer::EnemyBlow(void)
{
	// �͈͂ƈЗ�
	const float fBlowRange = 100.0f;	// �L���͈�
	const float fBlowPower = 50.0f;		// ������΂����x

	// �G�I�u�W�F�N�g�̐擪�擾
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	while (pObj != nullptr)
	{
		// �G�擾
		if (pObj->GetObjType() == CObject::TYPE_ENEMY)
		{
			// �L���X�g
			CEnemy* pEnemy = static_cast<CEnemy*>(pObj);

			// �G���W�擾
			D3DXVECTOR3 vEnemyPos = pEnemy->GetPos();

			// �v���C���[�Ƃ̋���
			D3DXVECTOR3 vDiff = vEnemyPos - m_pos;

			float fDist = D3DXVec3Length(&vDiff);

			// �͈͓��Ȃ琁����΂�
			if (fDist < fBlowRange)
			{
				// ���K��
				D3DXVec3Normalize(&vDiff, &vDiff);

				// ������΂�����
				D3DXVECTOR3 vBlow = vDiff * fBlowPower;

				// �G���ɑ��x��������
				pEnemy->AddBlow(vBlow);
				pEnemy->SetBlow(true);
			}
		}

		// ���̓G���擾
		pObj = pObj->GetNext();
	}
}