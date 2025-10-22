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
#include "number.h"
#include <fstream>

//===================================
// �R���X�g���N�^
//===================================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// �l���N���A����
	m_pos = VECTOR3_NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	
	for (int nCnt = 0;nCnt < MAX_RANK;nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_DIGIT; nNumber++)
		{
			m_apNumbers[nCnt][nNumber] = nullptr;
		}
	}

	for (auto& randata : m_RankData)
	{
		randata = NULL;
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

	// �I�u�W�F�N�g�ݒ�
	pRankScore->m_pos = pos;
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight=fHeight;

	// ���������s��
	if (FAILED(pRankScore->Init()))
	{
		return nullptr;
	}
	
	// �������ꂽ�|�C���^
	return pRankScore;
}
//===================================
// ����������
//===================================
HRESULT CRankingScore::Init(void)
{
	// �X�R�A�̃��[�h����
	Load();

	// �����v�Z
	float fTexPos = m_fWidth / MAX_DIGIT;

	for (int nRank = 0; nRank < MAX_RANK; nRank++)
	{
		// ������
		for (int nDigit = 0; nDigit < MAX_DIGIT; nDigit++)
		{
			// �C���X�^���X����
			m_apNumbers[nRank][nDigit] = new CNumber;

			// Y���W�����炷
			float yOffset = m_pos.y + (m_fHeight + 65.0f) * nRank;

			// ����������
			m_apNumbers[nRank][nDigit]->Init
			(
				D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nDigit), yOffset, 0.0f),
				fTexPos,
				m_fHeight
			);

			// �T�C�Y�ݒ�
			m_apNumbers[nRank][nDigit]->SetSize(fTexPos, m_fHeight);

			// �e�N�X�`���ݒ�
			m_apNumbers[nRank][nDigit]->SetTexture("score001.png");
		}
	}

	return S_OK;
}
//===================================
// �I������
//===================================
void CRankingScore::Uninit(void)
{
	// null�`�F�b�N
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_DIGIT; nNumber++)
		{
			if (m_apNumbers[nCnt][nNumber] != nullptr)
			{
				// �I������
				m_apNumbers[nCnt][nNumber]->Uninit();

				// �|�C���^�̔j��
				delete m_apNumbers[nCnt][nNumber];

				// null������
				m_apNumbers[nCnt][nNumber] = nullptr;
			}
		}
	}

	// ���g�̔j��
	CObject::Release();
}
//===================================
// �X�V����
//===================================
void CRankingScore::Update(void)
{
	// �����X�V
	for (int rank = 0; rank < MAX_RANK; rank++)
	{
		int nScore = m_RankData[rank];

		for (int digit = 0; digit < MAX_DIGIT; digit++)
		{
			int nNum = nScore % 10;
			nScore /= 10;

			// ���X�V
			m_apNumbers[rank][digit]->SetDigit(nNum);
		}
	}
}
//===================================
// �`�揈��
//===================================
void CRankingScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int nCntdigit = 0; nCntdigit < MAX_DIGIT; nCntdigit++)
		{
			// ������`��
			m_apNumbers[nCnt][nCntdigit]->Draw();
		}
	}
}
//===================================
// �Ǎ�����
//===================================
void CRankingScore::Load()
{
	// �J���t�@�C����I��
	std::ifstream OpenFile("data/SCORE/Ranking.txt");
	if (!OpenFile)
	{
		// ��O����
		MessageBox(GetActiveWindow(), "�t�@�C�����J���܂���", "Ranking.txt", MB_OK);
		return;
	}

	// �ǂݍ��񂾃f�[�^���i�[
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		if (!(OpenFile >> m_RankData[nCnt]))
		{
			// ���l������������0������
			m_RankData[nCnt] = 0;
		}
	}

	// �t�@�C�������
	OpenFile.close();
}