//======================================================
//
// �V�����b�_�[�Ǘ����� [ shreddermanager.cpp ]
// Author: Soichiro Sasaki
//
//======================================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "shredbinmanager.h"
#include "shredbineffect.h"
#include "input.h"
#include "manager.h"

int CShredbinManager::m_nNum = 0;

//===============================
// �R���X�g���N�^
//===============================
CShredbinManager::CShredbinManager()
{
	m_pos = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CShredbinManager::~CShredbinManager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CShredbinManager::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 20.0f, -200.0f);

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredbinManager::Uninit(void)
{

}
//===============================
// �X�V����
//===============================
void CShredbinManager::Update(void)
{
	CInputKeyboard* pKey = CManager::GetInputKeyboard();

	if (pKey->GetPress(DIK_9))
	{
		m_nNum++;
	}
	else if(pKey->GetPress(DIK_8)&&m_nNum>0)
	{
		m_nNum--;
	}

	if (m_nNum > CShredbinEffect::GetNumAll())
	{
		CShredbinEffect::Create(m_pos, D3DXVECTOR3(200.0f, 200.0f, 200.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5);
	}
}