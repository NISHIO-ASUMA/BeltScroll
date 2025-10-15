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
#include "meshfield.h"
#include "titlelogo.h"
#include "ui.h"

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
	// ���b�V���t�B�[���h
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// ���S���� ( �̂��Ƀe�N�X�`���ύX )
	CTitleLogo::Create(D3DXVECTOR3(1200.0f, 70.0f, 0.0f));

	// UI����
	CUi::Create(CENTERPOS, 0, 300.0f, 80.0f, "GameName.png", false);
	CUi::Create(D3DXVECTOR3(640.0f,560.0f,0.0f), 0, 220.0f, 60.0f, "Enterkey.png", false);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CTitle::Uninit(void)
{
	// ����
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