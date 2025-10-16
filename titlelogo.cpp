//=====================================
//
// �^�C�g�����S���� [ titlelogo.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "titlelogo.h"

//****************************
// �萔��Ԑ錾
//****************************
namespace LOGOINFO
{
	constexpr float WIDTH = 60.0f; // ����
	constexpr float HEIGHT = 60.0f; // ����
}

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
}
//================================
// �f�X�g���N�^
//================================
CTitleLogo::~CTitleLogo()
{
	// ����
}
//================================
// ��������
//================================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleLogo* pLogo = new CTitleLogo;
	if (pLogo == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLogo->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pLogo->SetPos(pos);
	pLogo->SetHeight(LOGOINFO::HEIGHT);
	pLogo->SetWidth(LOGOINFO::WIDTH);
	pLogo->SetAnchor(ANCHORTYPE_CENTER);
	pLogo->SetTexture("TitleLogo.png");

	// �������ꂽ�|�C���^
	return pLogo;
}
//================================
// ����������
//================================
HRESULT CTitleLogo::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ����������
	return S_OK;
}
//================================
// �I������
//================================
void CTitleLogo::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CTitleLogo::Update(void)
{
	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CTitleLogo::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}