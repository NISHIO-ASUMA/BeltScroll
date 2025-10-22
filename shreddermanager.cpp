//======================================================
//
// �V�����b�_�[�Ǘ����� [ shreddermanager.cpp ]
// Author: Asuma Nishio
//
//======================================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "shreddermanager.h"
#include "shredder.h"

//===============================
// �R���X�g���N�^
//===============================
CShredderManager::CShredderManager()
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pShredder[nCnt] = nullptr;
	}
	m_nSwapCnt = 0;
	m_bRedFlont = true;
}
//===============================
// �f�X�g���N�^
//===============================
CShredderManager::~CShredderManager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CShredderManager::Init(void)
{

	m_pShredder[TYPE_RED]=CShredder::Create(D3DXVECTOR3(-400.0f, 0.0f, -250.0f), TYPE_RED);
	m_pShredder[TYPE_GREEN]=CShredder::Create(D3DXVECTOR3(-400.0f, 0.0f, 250.0f), TYPE_GREEN);

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredderManager::Uninit(void)
{

}
//===============================
// �X�V����
//===============================
void CShredderManager::Update(void)
{
	Swap();
}

//===============================
// ��������
//===============================
void CShredderManager::Swap(void)
{
	// ��������^�C�~���O
	if (m_nSwapCnt > SWAPCOUNT)
	{
		m_bRedFlont = !m_bRedFlont;
		m_nSwapCnt = 0;
	}

	// �ʒu���������鏈��
	if (m_bRedFlont)
	{
		m_pShredder[0]->SetPosZ(FIXED_Z00);
		m_pShredder[1]->SetPosZ(FIXED_Z01);
	}
	else
	{
		m_pShredder[0]->SetPosZ(FIXED_Z01);
		m_pShredder[1]->SetPosZ(FIXED_Z00);
	}

	m_nSwapCnt++;
}
