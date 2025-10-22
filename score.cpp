//===================================
//
// �X�R�A���� [ score.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "score.h"
#include "number.h"
#include "manager.h"
#include <fstream>

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
int CScore::m_nScore = NULL;

//=================================
// �R���X�g���N�^
//=================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_pos = VECTOR3_NULL;

	for (auto& number : m_pNumber)
	{
		number = nullptr;
	}
}
//=================================
// �f�X�g���N�^
//=================================
CScore::~CScore()
{
	// ����
}
//=================================
// ��������
//=================================
CScore* CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CScore* pScore = new CScore;
	if (pScore == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;
	pScore->m_pos = pos;

	// ���������s��
	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	// �C���X�^���X���ەԂ�
	return pScore;
}
//=================================
// ����������
//=================================
HRESULT CScore::Init(void)
{
	// ���̕��������v�Z
	float fTexPos = m_fWidth / SCORE_NUM;

	// ������
	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
	{
		// �i���o�[�I�u�W�F�N�g�̐���
		m_pNumber[nCnt] = new CNumber;

		// ����������
		m_pNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);

		// �i���o�[�ϐ��̃T�C�Y
		m_pNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// ���W�ݒ�
		m_pNumber[nCnt]->SetPos(m_pos);


		// �e�N�X�`���Z�b�g
		m_pNumber[nCnt]->SetTexture("number003.png");
	}

	return S_OK;
}
//=================================
// �I������
//=================================
void CScore::Uninit(void)
{
	// null�`�F�b�N
	for (auto& number : m_pNumber)
	{
		if (number != nullptr)
		{
			// �I������
			number->Uninit();

			// �|�C���^�̔j��
			delete number;

			// null������
			number = nullptr;
		}
	}

	CObject::Release();
}
//=================================
// �X�V����
//=================================
void CScore::Update(void)
{
	// �X�R�A�i�[
	int nScore = m_nScore;

	// ������
	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		// �������Ƃɕ�������l���v�Z
		int nDigit = nScore % SCORE_NUM;
		nScore /= SCORE_NUM;

		// ���X�V
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}
//=================================
// �`�揈��
//=================================
void CScore::Draw(void)
{
	// �g���Ă��錅�����̕`��
	for (int nCnt = 0; nCnt < SCORE_NUM; nCnt++)
	{
		// �i���o�[�`��
		m_pNumber[nCnt]->Draw();
	}
}
//=================================
// �����o������
//=================================
void CScore::Save(void)
{
	// �J���t�@�C�����Z�b�g
	std::ofstream OpenFile("data/SCORE/GameScore.txt");
	if (!OpenFile)
	{
		// ��O����
		MessageBox(GetActiveWindow(), "�X�R�A�ۑ����s", "�t�@�C�����J���܂���", MB_OK);
		return;
	}

	// �X�R�A�����o��
	OpenFile << m_nScore;

	// �t�@�C�������
	OpenFile.close();
}