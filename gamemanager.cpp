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

//******************************
// �ÓI�����o�ϐ�
//******************************
CGameManager* CGameManager::m_pInstance = nullptr;

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
	// TODO : ���ؗp����
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

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

}
//===============================
// �`�揈��
//===============================
void CGameManager::Draw(void)
{

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