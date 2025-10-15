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
#include "meshfield.h"

//=====================================
// �R���X�g���N�^
//=====================================
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
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

	// CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

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
	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �����L���O
		CManager::GetFade()->SetFade(new CGame());

		return;
	}

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
CTitle* CTitle::Create()
{
	// �C���X�^���X����
	CTitle* pTitle = new CTitle();

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