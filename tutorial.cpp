//=====================================
//
// �`���[�g���A������ [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorial.h"
#include "manager.h"
#include "sound.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{

}
//===============================
// �f�X�g���N�^
//===============================
CTutorial::~CTutorial()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CTutorial::Init(void)
{
	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_TUTORIALBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CTutorial::Uninit(void)
{

}
//===============================
// �X�V����
//===============================
void CTutorial::Update(void)
{

}
//===============================
// �`�揈��
//===============================
void CTutorial::Draw(void)
{
	// ����
}
//===============================
// ��������
//===============================
CTutorial* CTutorial::Create(void)
{
	// �C���X�^���X����
	CTutorial* pTutorial = new CTutorial;

	// �������s��
	if (pTutorial == nullptr) return nullptr;

	// �����������Ɏ��s������
	if (FAILED(pTutorial->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTutorial;
}