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
#include "texture.h"
#include "manager.h"

//==============================
// �R���X�g���N�^
//==============================
CBlowerUi::CBlowerUi(int nPriority) : CObject2D(nPriority) , m_nIdxTexture(-1)
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
CBlowerUi* CBlowerUi::Create(D3DXVECTOR3 pos, int nType)
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
	pBlowUi->SetTexture(nType);
	pBlowUi->SetSize(200.0f, 60.0f);
	pBlowUi->SetAnchor(ANCHORTYPE_CENTER);

	// ���������|�C���^
	return pBlowUi;
}
//==============================
// ����������
//==============================
HRESULT CBlowerUi::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(TYPE_BLOWERUI);

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
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �e�N���X����
	CObject2D::Draw();
}
//================================
// �e�N�X�`�����蓖��
//================================
void CBlowerUi::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^���}�l�[�W���[����擾
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// ��ނɂ���ăe�N�X�`�����蓖�Ă�؂�ւ���
	switch (nType)
	{
	case TYPE_SMALL: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_small.png"); 		// �e�N�X�`�����蓖��
		break;

	case TYPE_MIDIUM: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_midium.png"); 		// �e�N�X�`�����蓖��
		break;

	case TYPE_FULL: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_max.png"); 	// �e�N�X�`�����蓖��
		break;

	default:
		m_nIdxTexture = -1;
		break;
	}

}