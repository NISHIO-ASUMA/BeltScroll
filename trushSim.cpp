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
#include "collider.h"
#include "collision.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CTrushSim::CTrushSim(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_posOld = VECTOR3_NULL;
	m_pCollider = nullptr;
	m_fJump = 0.0f;
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

	m_pCollider = CSphereCollider::Create(GetPos(), 20.0f);
	return S_OK;
}
//================================
// �I������
//================================
void CTrushSim::Uninit(void)
{
	delete m_pCollider;
	m_pCollider = nullptr;

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
	D3DXMATRIX mtx = GetMtxWorld();
	D3DXVECTOR3 pos;
	pos = CObjectX::GetPos();

	D3DXVECTOR3 rot = CObjectX::GetRot();
	// ���͂ƃJ�����擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	CCamera* pCamera = CManager::GetCamera();

	m_posOld = pos;

	if (GetParent() != nullptr)
	{
		pos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
	}

	if (pKeyboard->GetPress(DIK_UP))
	{// ����
		pos.x += sinf(pCamera->GetRot().y) * SPEED;
		pos.z += cosf(pCamera->GetRot().y) * SPEED;

	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{// ��O
		pos.x -= sinf(pCamera->GetRot().y) * SPEED;
		pos.z -= cosf(pCamera->GetRot().y) * SPEED;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{// �E����
		pos.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
		pos.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;

	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{// ������
		pos.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
		pos.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
	}
	else
	{
		pos = CObjectX::GetPos();
	}

	if (pKeyboard->GetTrigger(DIK_RSHIFT))
	{// ������
		m_fJump = JUMP;
	}

	if (GetParent() != nullptr)
	{
		CObjectX* parent = GetParent();
		D3DXMATRIX parentMtx = parent->GetMtxWorld();
		// �t�s��쐬
		D3DXMATRIX invMtx;

		D3DXMatrixInverse(&invMtx, nullptr, &parentMtx);

		D3DXVECTOR3 wldPos = pos;
		D3DXVECTOR3 lclPos;

		D3DXVec3TransformCoord(&pos, &wldPos, &invMtx);
	}

	m_fJump -= 0.1f;

	pos.y += m_fJump;

	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
		m_fJump = 0.0f;
	}

	// ���f
	m_pCollider->SetPos(pos);
	CObjectX::SetPos(pos);
}

//================================
// �����蔻��
//================================
bool CTrushSim::Collision(CSphereCollider*pCollider)
{
	return CSphereSphereCollision::Collision(m_pCollider, pCollider);
}