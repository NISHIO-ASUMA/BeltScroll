//=====================================
//
// ���������� [ gimmickfloor.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "trushSim.h"
#include "manager.h"
#include "input.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CTrushSim::CTrushSim(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_posOld = VECTOR3_NULL;
}
//================================
// �f�X�g���N�^
//================================
CTrushSim::~CTrushSim()
{
	// ����
}
//================================
// ��������
//================================
CTrushSim* CTrushSim::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// �C���X�^���X����
	CTrushSim* pBlock = new CTrushSim;
	if (pBlock == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(Scale);
	pBlock->SetFilePass(FileName);

	// ���������s��
	if (FAILED(pBlock->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pBlock;
}
//================================
// ����������
//================================
HRESULT CTrushSim::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	return S_OK;
}
//================================
// �I������
//================================
void CTrushSim::Uninit(void)
{
	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CTrushSim::Update(void)
{
	// ����
	Controll();

	// �e�N���X�̍X�V
	CObjectX::Update();
}
//================================
// �`�揈��
//================================
void CTrushSim::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}

//================================
// ����������
//================================
void CTrushSim::Controll(void)
{
	// �ʒu�ƌ����擾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 rot = CObjectX::GetRot();
	// ���͂ƃJ�����擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	CCamera* pCamera = CManager::GetCamera();

	if (pKeyboard->GetPress(DIK_UP))
	{// ����
		pos.x += sinf(pCamera->GetRot().y) * 0.1f;
		pos.z += cosf(pCamera->GetRot().y) * 0.1f;

	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{// ��O
		pos.x -= sinf(pCamera->GetRot().y) * 0.1f;
		pos.z -= cosf(pCamera->GetRot().y) * 0.1f;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{// �E����
		pos.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 0.1f;
		pos.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 0.1f;

	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{// ������
		pos.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * 0.1f;
		pos.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * 0.1f;

	}

	// ���f
	CObjectX::SetPos(pos);
}

//================================
// �����蔻��
//================================
bool CTrushSim::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// ������Ȃ���
	return false;
}