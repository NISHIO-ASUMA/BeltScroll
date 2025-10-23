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
#include "loseplayer.h"

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
	// ���U���g�v���C���[����
	CLosePlayer::Create(D3DXVECTOR3(0.0f,0.0f,-200.0f));

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