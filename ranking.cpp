//=======================================
//
// �����L���O�V�[������ [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "ranking.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "ui.h"
#include "rankingscore.h"

//===================================
// �I�[�o�[���[�h�R���X�g���N�^
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	// �l�̃N���A

}
//===================================
// �f�X�g���N�^
//===================================
CRanking::~CRanking()
{
	// ����
}
//===================================
// ����������
//===================================
HRESULT CRanking::Init(void)
{
	// ui����
	CUi::Create(CENTERPOS, 0, 640.0f, 360.0f, "ranking.jpg", false);

	// �����L���OBGM�Đ�
	// CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RANKINGBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===================================
// �I������
//===================================
void CRanking::Uninit(void)
{

}
//===================================
// �X�V����
//===================================
void CRanking::Update(void)
{
	// ����L�[����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// �^�C�g���J��
		pFade->SetFade(std::make_unique<CTitle>());

		return;
	}
}
//===================================
// �`�揈��
//===================================
void CRanking::Draw(void)
{
	// ����
}