//============================================
//
// �������U���g�V�[������ [ loseresult.cpp ]
// Author: Asuma Nishio
//
//============================================

//***********************
// �C���N���[�h�t�@�C��
//***********************
#include "loseresult.h"
#include "ui.h"
#include "manager.h"
#include "fade.h"
#include "ranking.h"

//==============================
// �R���X�g���N�^
//==============================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// �l�̃N���A
}
//==============================
// �f�X�g���N�^
//==============================
CLoseResult::~CLoseResult()
{

}
//==============================
// ����������
//==============================
HRESULT CLoseResult::Init(void)
{
	// UI����
	CUi::Create(CENTERPOS, 0, 640.0f, 360.0f, "gameover.jpg", false);

	return S_OK;
}
//==============================
// �I������
//==============================
void CLoseResult::Uninit(void)
{

}
//==============================
// �X�V����
//==============================
void CLoseResult::Update(void)
{
	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// ��ʑJ��
		pFade->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//==============================
// �`�揈��
//==============================
void CLoseResult::Draw(void)
{
	// ����
}