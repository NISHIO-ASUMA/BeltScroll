//====================================
//
// ���U���g�V�[������ [ result.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "result.h"
#include "ui.h"
#include "manager.h"
#include "ranking.h"

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT)
{
}
//=================================
// �f�X�g���N�^
//=================================
CResult::~CResult()
{
	// ����
}
//=================================
// ��������
//=================================
CResult* CResult::Create(void)
{
	// �C���X�^���X����
	CResult* pResult = new CResult;

	// �����Ɏ��s������
	if (pResult == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pResult->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pResult;
}
//=================================
// ����������
//=================================
HRESULT CResult::Init(void)
{
	// ui����
	CUi::Create(CENTERPOS,0,640.0f,360.0f,"GameClear.png",false);

	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CResult::Uninit(void)
{

}
//=================================
// �X�V����
//=================================
void CResult::Update(void)
{
	// �L�[���͂őJ��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// �����L���O
		CManager::GetFade()->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//=================================
// �`�揈��
//=================================
void CResult::Draw(void)
{
	// ����
}
