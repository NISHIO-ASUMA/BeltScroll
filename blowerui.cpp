//====================================
//
// �u�����[UI���� [ blowerui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "blowerui.h"

//***************************
// �萔���
//***************************
namespace BLOWUI
{


};

//==============================
// �R���X�g���N�^
//==============================
CBlowerUi::CBlowerUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
}
//==============================
// �f�X�g���N�^
//==============================
CBlowerUi::~CBlowerUi()
{
	// ����
}
//==============================
// ��������
//==============================
CBlowerUi* CBlowerUi::Create(D3DXVECTOR3 pos, const char* pFileName)
{
	// �C���X�^���X����
	CBlowerUi* pBlowUi = new CBlowerUi;
	if (pBlowUi == nullptr) return nullptr;

	if (FAILED(pBlowUi->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pBlowUi->SetPos(pos);
	pBlowUi->SetTexture(pFileName);
	pBlowUi->SetSize(60.0f, 60.0f);
	pBlowUi->SetAnchor(ANCHORTYPE_CENTER);

	// ���������|�C���^
	return pBlowUi;
}
//==============================
// ����������
//==============================
HRESULT CBlowerUi::Init(void)
{
	// �e�N���X����
	CObject2D::Init();

	return S_OK;
}
//==============================
// �I������
//==============================
void CBlowerUi::Uninit(void)
{
	// �e�N���X����
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CBlowerUi::Update(void)
{
	// �e�N���X����
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CBlowerUi::Draw(void)
{
	// �e�N���X����
	CObject2D::Draw();
}