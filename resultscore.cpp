//===========================================
//
// ���U���g�p�X�R�A���� [ resultscore.cpp ]
// Author: Asuma Nishio
//
//===========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "resultscore.h"
#include "number.h"
#include <fstream>

//=====================
// �R���X�g���N�^
//=====================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nLoadScore = NULL;

	for (auto& number : m_pNumber)
	{
		number = nullptr;
	}
}
//=====================
// �f�X�g���N�^
//=====================
CResultScore::~CResultScore()
{
	// ����
}
//=====================
// ��������
//=====================
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CResultScore* presult = new CResultScore;
	if (presult == nullptr) return nullptr;

	// �l���Z�b�g
	presult->m_pos = pos;
	presult->m_fHeight = fHeight;
	presult->m_fWidth = fWidth;
	
	// ���������s��
	if (FAILED(presult->Init())) 	return nullptr;

	// �������ꂽ�C���X�^���X
	return presult;
}
//=====================
// ����������
//=====================
HRESULT CResultScore::Init(void)
{
	// �X�R�A�ǂݍ���
	Load();

	// ���̕��������v�Z
	float fTexPos = m_fWidth / RESULT_SCORE;

	// �i���o�[����
	for (int nCnt = 0; nCnt < RESULT_SCORE; nCnt++)
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
//=====================
// �I������
//=====================
void CResultScore::Uninit(void)
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
//=====================
// �X�V����
//=====================
void CResultScore::Update(void)
{
	// �����X�V
	int nScore = m_nLoadScore;

	// ������
	for (int nCntScore = 0; nCntScore < RESULT_SCORE; nCntScore++)
	{
		// �������Ƃɕ�������l���v�Z
		int nDigit = nScore % RESULT_SCORE;
		nScore /= RESULT_SCORE;

		// ���X�V
		m_pNumber[nCntScore]->SetDigit(nDigit);
	}
}
//=====================
// �`�揈��
//=====================
void CResultScore::Draw(void)
{
	// �i���o�[�I�u�W�F�N�g�`��
	for (int nCnt = 0; nCnt < RESULT_SCORE; nCnt++)
	{
		// �i���o�[�`��
		m_pNumber[nCnt]->Draw();
	}
}
//=====================
// �ǂݍ��ݏ���
//=====================
void CResultScore::Load(void)
{
	// �J���t�@�C�����Z�b�g
	std::ifstream OpenFile("data/SCORE/GameScore.txt");
	if (!OpenFile)
	{
		// ��O����
		MessageBox(GetActiveWindow(), "�t�@�C�����J���܂���", "���U���g�X�R�A�ǂݍ���", MB_OK);
		return;
	}

	// �ǂݎ�����f�[�^���Z�b�g
	OpenFile >> m_nLoadScore;

	// �t�@�C�������
	OpenFile.close();
}