//===================================
//
// �G�̏��� [ enemy.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "enemy.h"
#include "shadow.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"

//==============================
// �R���X�g���N�^
//==============================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_Oldpos = VECTOR3_NULL;
	m_move = VECTOR3_NULL;
	m_scale = INITSCALE;

	D3DXMatrixIdentity(&m_mtxworld);

	m_pScriptName = nullptr;
	m_pShadow = nullptr;
	m_pMotion = nullptr;

	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}
//==============================
// �f�X�g���N�^
//==============================
CEnemy::~CEnemy()
{
	// ����
}
//==============================
// ��������
//==============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName)
{
	// �C���X�^���X����
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// �l����
	pEnemy->m_pos = pos;
	pEnemy->m_rot = rot;
	pEnemy->m_pScriptName = pScriptName;

	// ���������s��
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�C���X�^���X��Ԃ�
	return pEnemy;
}
//==============================
// ����������
//==============================
HRESULT CEnemy::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_ENEMY);

	// �|�C���^����
	m_pMotion = CMotion::Load(m_pScriptName, ENEMY_MODEL, m_pModel, ENEMYMOTION_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(ENEMYMOTION_MAX);

	// �V���h�E����
	m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x,2.0f,m_pos.z), m_rot);

	// �ړ��ʂ��Z�b�g
	m_move.x = 3.0f;
	m_move.z = 3.0f;

	return S_OK;
}
//==============================
// �I������
//==============================
void CEnemy::Uninit(void)
{
	// null�`�F�b�N
	if (m_pMotion != nullptr)
	{
		// �j��
		delete m_pMotion;

		// null������
		m_pMotion = nullptr;
	}

	// �g�p�������f�����̔j��
	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		// null�`�F�b�N
		if (m_pModel[nCnt] != nullptr)
		{
			// �I������
			m_pModel[nCnt]->Uninit();

			// �j��
			delete m_pModel[nCnt];

			// null������
			m_pModel[nCnt] = nullptr;
		}
	}

	// ���g�̔j��
	CObject::Release();
}
//==============================
// �X�V����
//==============================
void CEnemy::Update(void)
{
	// �v���C���[�擾
	CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer();
	if (pPlayer == nullptr) return;

	// �v���C���[�Ɍ������Ă��鏈��
	D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�ʒu�擾
	D3DXVECTOR3 dir = playerPos - m_pos;		// �v���C���[�ւ̃x�N�g��
	float dist = D3DXVec3Length(&dir);			// ����

	D3DXVec3Normalize(&dir, &dir);			// ���K��
	float speed = 0.6f;						// �Ǐ]�X�s�[�h
	m_move += dir * speed;					// �ړ��x�N�g���ɉ��Z

	// �ߋ��̈ʒu����ۑ�
	m_Oldpos = m_pos;

	// �ʒu�X�V
	m_pos += m_move;

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	 // �X�e���V���V���h�E������
	if (m_pShadow)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 2.0f, m_pos.z));
		m_pShadow->SetRot(m_rot);
	}

	// ���[�V�����X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_pModel, ENEMY_MODEL);
	}
}
//==============================
// �`�揈��
//==============================
void CEnemy::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, m_scale.x, m_scale.y, m_scale.z);
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
	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		m_pModel[nCnt]->Draw();
	}
}