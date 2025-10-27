//=====================================
//
// ���C���Q�[������ [ game.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "game.h"
#include "manager.h"
#include "debugproc.h"
#include "title.h"
#include "result.h"
#include "meshfield.h"
#include <memory>
#include "goal.h"
#include "player.h"

//**************************
// �萔���
//**************************
namespace GAMEINFO
{
	constexpr int GAMECOUNT = 30; // ���U���g�J�ڃJ�E���g
};

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CPauseManager* CGame::m_pPausemanager = nullptr; // �|�[�Y�}�l�[�W���[�̃|�C���^
CGameManager* CGame::m_pGameManager = nullptr;	// �Q�[���}�l�[�W���[�̃|�C���^

//==================================
// �R���X�g���N�^
//==================================
CGame::CGame() : CScene(CScene::MODE_GAME),m_nGametype(GAMESTATE_NONE),m_nStateCount(NULL)
{
	// �l�̃N���A
}
//==================================
// �f�X�g���N�^
//==================================
CGame::~CGame()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CGame::Init(void)
{
	// �|�[�Y�}�l�[�W���[����
	m_pPausemanager = new CPauseManager;

	// null��������
	if (m_pPausemanager == nullptr)
	{
		return E_FAIL;
	}

	// �|�[�Y�}�l�[�W���[����������
	m_pPausemanager->Init();

	// �}�l�[�W���[����
	m_pGameManager = new CGameManager;
	m_pGameManager->Init();

	// �ʏ�i�s���
	m_nGametype = GAMESTATE_NORMAL;


	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CGame::Uninit(void)
{
	// null�`�F�b�N
	if (m_pPausemanager != nullptr)
	{
		// �I������
		m_pPausemanager->Uninit();

		// �|�C���^�̔j��
		delete m_pPausemanager;

		// nullptr�ɂ���
		m_pPausemanager = nullptr;
	}

	// null�`�F�b�N
	if (m_pGameManager != nullptr)
	{
		// �I������
		m_pGameManager->Uninit();

		// �|�C���^�̔j��
		delete m_pGameManager;

		// nullptr�ɂ���
		m_pGameManager = nullptr;
	}
}
//==================================
// �X�V����
//==================================
void CGame::Update(void)
{	
	// �|�[�Y�̃L�[���͔���
	m_pPausemanager->SetEnablePause();
	
	// �|�[�Y�̍X�V����
	m_pPausemanager->Update();
	
	// �t�F�[�h�擾
	CFade* pFade = CManager::GetFade();

	switch (m_nGametype)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END:
		m_nStateCount++;

		if (m_nStateCount >= 30)
		{
			// �J�E���^�[��������
			m_nStateCount = 0;
			
			// 1�b�o��
			m_nGametype = GAMESTATE_NONE;//�������Ă��Ȃ����

			// �t�F�[�h���擾�ł�����
			if (pFade != nullptr)
			{
				// ���U���g�V�[���ɑJ��
				pFade->SetFade(std::make_unique<CResult>());

				// �����ŏ�����Ԃ�
				return;
			}
		}
		break;

	case GAMESTATE_LOSEEND:
		m_nStateCount++;

		if (m_nStateCount >= GAMEINFO::GAMECOUNT)
		{
			// �J�E���^�[��������
			m_nStateCount = 0;

			// 1�b�o��
			m_nGametype = GAMESTATE_NONE;

			// �t�F�[�h���擾�ł�����
			if (pFade != nullptr)
			{
				//// �������U���g�V�[���ɑJ��
				//pFade->SetFade(new CLoseResult());

				// �����ŏ�����Ԃ�
				return;
			}
		}
		break;
	}

	// false�̎��ɍX�V
	if (m_nGametype == GAMESTATE_NORMAL &&
		m_pPausemanager->GetPause() == false)
	{
		// �Q�[���}�l�[�W���[�X�V
		m_pGameManager->Update();

		// �S�[���擾
		auto Goal = m_pGameManager->GetGoal();
		if (Goal == nullptr) return;

		// �v���C���[�擾
		auto Player = m_pGameManager->GetPlayer();
		if (Player == nullptr) return;

		// �͈͓��ɂ��邩����
		if (Goal->CheckPos(Player->GetPos()))
		{
			// �^�C�v�ύX
			m_nGametype = GAMESTATE_END;

			// �v���C���[�̓������~�߂�
			Player->SetMove(VECTOR3_NULL);
			return;
		}

		//// �o�ߎ��Ԃ��擾
		//int Numtime = m_pGameManager->GetTime()->GetAllTime();

		//// �^�C�}�[��0�b�ȉ��Ȃ�
		//if (Numtime <= 0)
		//{
		//	// �������U���g�J��
		//	m_nGametype = GAMESTATE_LOSEEND;
		//	return;
		//}

		// ��ԕύX
		// m_nGametype = GAMESTATE_END;
	}
}
//==================================
// �`�揈��
//==================================
void CGame::Draw(void)
{
	// ����
}
//==================================
// �R���X�g���N�^
//==================================
CGame* CGame::Create(void)
{	
	// �C���X�^���X����
	CGame* pGame = new CGame;

	// nullptr��������
	if (pGame == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pGame->Init()))
	{
		// �|�C���^��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pGame;
}