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

//===============================
// �R���X�g���N�^
//===============================
CGameManager::CGameManager()
{
	// �l�̃N���A
	m_pBlockManager = nullptr;
	m_pPlayer = nullptr;
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
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// �v���C���[���� ( �̂��Ƀ��f���ύX )
	m_pPlayer = CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");

	// �G����
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");
	CEnemy::Create(D3DXVECTOR3(-550.0f,0.0f,-550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MOTION/Enemy/MotionEnemy.txt");

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
}
//===============================
// �X�V����
//===============================
void CGameManager::Update(void)
{
	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �����L���O
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
