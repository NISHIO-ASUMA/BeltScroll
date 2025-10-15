//=======================================
//
// �����L���O�V�[������ [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "ranking.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "ui.h"
#include "rankingscore.h"
#include "number.h"

//******************************
// �ÓI�����o�ϐ�
//******************************
CRankingScore* CRanking::m_Score[MAX_RANK] = {};

//===================================
// �I�[�o�[���[�h�R���X�g���N�^
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	//CObject::SetObjType(CObject::TYPE_SCENE);

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		//m_Score[nCnt] = NULL;
		m_nNumData[nCnt] = 0;
	}
}
//===================================
// �f�X�g���N�^
//===================================
CRanking::~CRanking()
{
	// ����
}
//===================================
// ��������
//===================================
CRanking* CRanking::Create(void)
{
	// �C���X�^���X����
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pRanking->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRanking;
}
//===================================
// ����������
//===================================
HRESULT CRanking::Init(void)
{
	//// �T�E���h�ւ̃|�C���^(�T�E���h�̎擾)
	//CSound* pSound = CManager::GetSound();

	// ���ʂ̐�
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_Score[nCnt] = CRankingScore::Create(D3DXVECTOR3(1100.0f, 200.0f + 100.0f * nCnt, 0.0f), 100.0f, 100.0f);
	}

	TxtLoad("data\\Text\\Rank.txt");	// �Ǎ�

	SetSort();	// ���ёւ�

	//// BGM�𗬂�
	//pSound->PlaySound(CSound::SOUND_LABEL_RESULTDATA);

	// ui����
	CUi::Create(CENTERPOS, 0, 640.0f, 360.0f, "RankBack.jpg", false);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===================================
// �I������
//===================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_apNumbers[nCnt]->CNumber::Uninit();
	}

}
//===================================
// �X�V����
//===================================
void CRanking::Update(void)
{
	// ����L�[����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// ��ʑJ��
		pFade->SetFade(new CTitle());

		return;
	}
}
//===================================
// �`�揈��
//===================================
void CRanking::Draw(void)
{
	// ����
}

//===================================
// �����L���O�̓��֏���(�~��)
//===================================
void CRanking::SetSort(void)
{
	//int nScore = CScore::Load("data\\txt\\Score.txt");

	int nNumData[MAX_RANK + 1] = { 0 };	// �����L���O�X�R�A�i�[�p

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nNumData[nCnt] = m_nNumData[nCnt];
	}

	//nNumData[MAX_RANK] = nScore;

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nSelect = nCntRank + 1; nSelect < MAX_RANK + 1; nSelect++)
		{
			if (nNumData[nCntRank] < nNumData[nSelect])
			{
				int nRankSave = nNumData[nCntRank];	// �ꎞ�ۑ�

				// ���l�̓���ւ�
				nNumData[nCntRank] = nNumData[nSelect];
				nNumData[nSelect] = nRankSave;
			}
		}
	}

	// �����L���O�̑��
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_nNumData[nCnt] = nNumData[nCnt];
	}

	// �����L���O�̕ۑ�
	TxtSave("data\\Text\\Rank.txt");
}

//===================================
// �����L���O�̓Ǎ�����
//===================================
void CRanking::TxtLoad(const char* pFileName)
{
	// �t�@�C�����J��
	FILE* pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{
		// ������i�[�p�ϐ�
		char aString[32] = {};
		char cData = {};
		int nRank[MAX_RANK] = { 0 };

		while (1)
		{
			cData = fscanf(pFile, "%s", &aString[0]);

			// ��������������
			if ((int)aString[0] == EOF || (char)aString[0] == NULL)
			{
				// ���[�v�𔲂���
				break;
			}
			else if (strcmp(&aString[0], "RANKING") == 0)
			{
				// �����̓ǂݎ��
				for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
				{
					cData = fscanf(pFile, "%d", &nRank[nCnt]);
				}
			}
			else if (strcmp(&aString[0], "END_RANKING") == 0)
			{
				// �X�R�A�̕ۑ�
				for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
				{
					m_nNumData[nCnt] = nRank[nCnt];
				}

				// �t�@�C�������
				fclose(pFile);

				// ���[�v�𔲂���
				break;
			}
		}
	}
}

//===================================
// �����L���O�̕ۑ�����
//===================================
void CRanking::TxtSave(const char* pFileName)
{
	// �t�@�C�����J��
	FILE* pFile = fopen(pFileName, "w");

	if (pFile != nullptr)
	{
		fprintf(pFile, "RANKING");

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "\n%d", m_nNumData[nCnt]);
		}
	}
}
