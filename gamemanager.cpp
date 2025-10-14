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
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");


	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CGameManager::Uninit(void)
{
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
	}

	// �����|�C���^��Ԃ�
	return m_pInstance;
}