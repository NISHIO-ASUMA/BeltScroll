//====================================
//
// �^�C�g������ [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"

//=====================================
// �R���X�g���N�^
//=====================================
CTitle::CTitle(bool isFirst) : CScene(CScene::MODE_TITLE), m_isCreate(isFirst)
{
	//����
}
//=====================================
// �f�X�g���N�^
//=====================================
CTitle::~CTitle()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CTitle::Init(void)
{
	// ui����
	// CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, 120.0f, 30.0f, "bullet.png", false);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CTitle::Uninit(void)
{

}
//=====================================
// �X�V����
//=====================================
void CTitle::Update(void)
{
	// �R���g���[���[�擾
	if (CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_BACK))
	{
		PostQuitMessage(0);
		return;
	}
}
//=====================================
// �`�揈��
//=====================================
void CTitle::Draw(void)
{
	// ����
}
//=====================================
// ��������
//=====================================
CTitle* CTitle::Create(bool isFirst)
{
	// �C���X�^���X����
	CTitle* pTitle = new CTitle(isFirst);

	// null��������
	if (pTitle == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTitle;
}