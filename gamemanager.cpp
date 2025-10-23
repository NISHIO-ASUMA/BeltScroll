//======================================================
//
// �Q�[���V�[���I�u�W�F�N�g�Ǘ����� [ gamemanager.cpp ]
// Author: Asuma Nishio
//
//======================================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "gamemanager.h"
#include "meshfield.h"
#include "ui.h"
#include "manager.h"
#include "result.h"
#include "player.h"
#include "blockmanager.h"
#include "shredder.h"
#include "enemymanager.h"
#include "trushSim.h"
#include "gimmickfloor.h"
#include "shreddermanager.h"
#include "loseresult.h"

//===============================
// �R���X�g���N�^
//===============================
CGameManager::CGameManager()
{
	// �l�̃N���A
	m_pBlockManager = nullptr;
	m_pPlayer = nullptr;
	m_pEnemyManager = nullptr;
	m_pTrushSim = nullptr;
}
//===============================
// �f�X�g���N�^
//===============================
CGameManager::~CGameManager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CGameManager::Init(void)
{
	//���b�V���t�B�[���h����
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 1000.0f, 1, 1);

	// �v���C���[���� ( �̂��Ƀ��f���ύX )
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player.txt");

	// �G�Ǘ��N���X���`
	m_pEnemyManager = CEnemyManager::Create();

	// �ǐ���

	m_pTrushSim = CTrushSim::Create(D3DXVECTOR3(0.0f, 30.0f, 0.0f), VECTOR3_NULL, INITSCALE, "data/MODEL/STAGEOBJ/block000.x");

	CGimmickFloor::Create(D3DXVECTOR3(400.0f, 100.0f, 0.0f), VECTOR3_NULL, INITSCALE, "data/MODEL/STAGEOBJ/gimmick.x");

	//// �}�b�v���f���z�u��񐶐�
	//m_pBlockManager = new CBlockManager;
	//m_pBlockManager->Init();

	m_pShredderManaher = new CShredderManager;
	m_pShredderManaher->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CGameManager::Uninit(void)
{
	// null�`�F�b�N
	if (m_pBlockManager != nullptr)
	{
		// �I������
		m_pBlockManager->Uninit();

		// �j��
		delete m_pBlockManager;

		// null������
		m_pBlockManager = nullptr;
	}

	// null�`�F�b�N
	if (m_pEnemyManager != nullptr)
	{
		// �I������
		m_pEnemyManager->Uninit();

		// �j��
		delete m_pEnemyManager;

		// null������
		m_pEnemyManager = nullptr;
	}

	if (m_pShredderManaher != nullptr)
	{
		// �I������
		m_pShredderManaher->Uninit();

		// �j��
		delete m_pShredderManaher;

		// null������
		m_pShredderManaher = nullptr;
	}
}
//===============================
// �X�V����
//===============================
void CGameManager::Update(void)
{
	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ���U���g
		CManager::GetFade()->SetFade(std::make_unique<CResult>());
		
		return;
	}

	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		// �����L���O
		CManager::GetFade()->SetFade(std::make_unique<CLoseResult>());

		return;
	}

	// null�`�F�b�N
	if (m_pEnemyManager != nullptr)
	{
		// �G�Ǘ��̍X�V����
		m_pEnemyManager->Update();
	}
	// null�`�F�b�N
	if (m_pShredderManaher != nullptr)
	{
		// �G�Ǘ��̍X�V����
		m_pShredderManaher->Update();
	}

}
//===============================
// �`�揈��
//===============================
void CGameManager::Draw(void)
{
	// �`�悷����̂�����΂����ɒǉ�
	// Object�p���̕��͏�����
}
