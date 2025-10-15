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
#include "enemy.h"

//******************************
// �ÓI�����o�ϐ�
//******************************
CGameManager* CGameManager::m_pInstance = nullptr; // �C���X�^���X

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
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// �v���C���[���� ( �̂��Ƀ��f���ύX )
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");

	// �G����
	CEnemy::Create(VECTOR3_NULL, VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");

	// ����
	m_pBlockManager = new CBlockManager;
	m_pBlockManager->Init();

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

	// �C���X�^���X�̔j��
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//===============================
// �X�V����
//===============================
void CGameManager::Update(void)
{
	// �L�[����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �J��
		CManager::GetFade()->SetFade(new CResult());

		return;
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
//===============================
// �C���X�^���X�擾
//===============================
CGameManager* CGameManager::GetInstance(void)
{
	// �C���X�^���X��null�Ȃ�
	if (m_pInstance == nullptr)
	{
		// �|�C���^����
		m_pInstance = new CGameManager();

		m_pInstance->m_pBlockManager = nullptr;
		m_pInstance->m_pPlayer = nullptr;

	}

	// �����|�C���^��Ԃ�
	return m_pInstance;
}