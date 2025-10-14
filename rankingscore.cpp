//=====================================
//
// �����L���O�X�R�A���� [ rankingscore.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "rankingscore.h"

//===================================
// �R���X�g���N�^
//===================================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_pos = VECTOR3_NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_ScoreNum = NULL;
	
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumbers[nCnt] = NULL;
	}
}

//===================================
// �f�X�g���N�^
//===================================
CRankingScore::~CRankingScore()
{
	// ���ɂȂ�
}

//===================================
// ��������
//===================================
CRankingScore* CRankingScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CRankingScore* pRankScore = new CRankingScore;

	pRankScore->m_pos = pos;
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight=fHeight;

	// ����������
	pRankScore->Init();

	return pRankScore;
}

//===================================
// ����������
//===================================
HRESULT CRankingScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumbers[nCnt]->Init(m_pos, m_fWidth, m_fHeight);
	}
	return S_OK;
}

//===================================
// �I������
//===================================
void CRankingScore::Uninit(void)
{
	// ���͂Ȃ�
}

//===================================
// �X�V����
//===================================
void CRankingScore::Update(void)
{
	// ���ɂȂ�
}

//===================================
// �`�揈��
//===================================
void CRankingScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// ������`��
		m_apNumbers[nCnt]->CNumber::Draw();
	}
}

//===================================
// �Ǎ�����
//===================================
int CRankingScore::Load(const char* pFileName)
{
	// �t�@�C�����J��
	FILE* pFile = fopen(pFileName, "r");

	int nLoad = { 0 };
	char cData = {};

	if (pFile != NULL)
	{
		// ������i�[�p�ϐ�
		char aString[32] = {};

		while (1)
		{
			cData = fscanf(pFile, "%s", &aString[0]);

			// ��������������
			if ((int)aString[0] == EOF || (char)aString[0] == NULL)
			{
				// �t�@�C�������
				fclose(pFile);

				// ���[�v�𔲂���
				break;
			}
		}
	}
	return nLoad;
}