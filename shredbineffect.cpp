//====================================
//
// �V�����b�h�r���G�t�F�N�g���� [ shredbinffect.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "shredbineffect.h"
#include "manager.h"
#include "shredbinmanager.h"

int CShredbinEffect::m_nNumAll = 0;

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CShredbinEffect::CShredbinEffect(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_oldPos = VECTOR3_NULL;
	m_size = VECTOR3_NULL;
	m_nIdx = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CShredbinEffect::~CShredbinEffect()
{
	m_nNumAll--;
}

//===============================
// ��������
//===============================
CShredbinEffect* CShredbinEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, float fRadius)
{
	// �G�t�F�N�g�|�C���^
	CShredbinEffect* pEffect = new CShredbinEffect;

	// nullptr��������
	if (pEffect == nullptr) return nullptr;

	// �������Ɏ��s������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// 3D�I�u�W�F�N�g�Z�b�g
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);
	pEffect->SetTexture("effect000.jpg");

	// ���a����
	pEffect->m_offsetPos = pos;
	pEffect->m_fRadius = fRadius;
	pEffect->m_size = size;
	pEffect->m_nIdx = m_nNumAll;
	m_nNumAll++;

	// �G�t�F�N�g�|�C���^��Ԃ�
	return pEffect;
}
//===============================
// ����������
//===============================
HRESULT CShredbinEffect::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();
	m_move.x = ((float)(rand() % 3) - 1.0f) * 3.0f;
	m_move.y = ((float)(rand() % 3) - 1.0f) * 3.0f;
	m_move.z = ((float)(rand() % 3) - 1.0f) * 3.0f;

	return S_OK;
}
//===============================
// �I������
//===============================
void CShredbinEffect::Uninit(void)
{
	// �e�N���X�̏I��
	CBillboard::Uninit();
}
//===============================
// �X�V����
//===============================
void CShredbinEffect::Update(void)
{
	// ���W,�J���[�擾
	D3DXVECTOR3 Effectpos = GetPos();
	m_oldPos = Effectpos;
	//�J���[�̐ݒ�
	D3DXCOLOR col = GetCol();

	// �I�u�W�F�N�g�X�V
	CBillboard::Update();

	D3DXVECTOR3 vec;

	// �ړ��ʂ̍X�V
	Effectpos += m_move;

	// ���Z����l��ݒ�
	const float fDecPow = 0.005f;

	// ���W���Z�b�g����
	SetPos(Effectpos);

	Collision();

	// 0�ȉ��Ȃ�
	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// �T�C�Y�Z�b�g
	SetSize(m_fRadius, m_fRadius);

	// 0�ȉ��̎�
	if (m_nIdx > CShredbinManager::GetNumAll())
	{
		// �폜����
		Uninit();
	}
}
//===============================
// �`�揈��
//===============================
void CShredbinEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���u�����f�B���O�̉��Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �r���{�[�h�`��
	CBillboard::Draw();

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���u�����f�B���O��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void CShredbinEffect::Collision(void)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_offsetPos.x + m_size.x * 0.5f <= pos.x && m_offsetPos.x + m_size.x * 0.5f > m_oldPos.x
		|| m_offsetPos.x - m_size.x * 0.5f >= pos.x && m_offsetPos.x - m_size.x * 0.5f < m_oldPos.x
		|| m_offsetPos.y + m_size.y * 0.5f <= pos.y && m_offsetPos.y + m_size.y * 0.5f > m_oldPos.y
		|| m_offsetPos.y - m_size.y * 0.5f >= pos.y && m_offsetPos.y - m_size.y * 0.5f < m_oldPos.y
		|| m_offsetPos.z + m_size.z * 0.5f <= pos.z && m_offsetPos.z + m_size.z * 0.5f > m_oldPos.z
		|| m_offsetPos.z - m_size.z * 0.5f >= pos.z && m_offsetPos.z - m_size.z * 0.5f < m_oldPos.z)
	{
		pos = m_oldPos;
		D3DXVECTOR3 vecPos;

		vecPos.x = ((float)(rand() % 100) - 50.0f);
		vecPos.y = ((float)(rand() % 100) - 50.0f);
		vecPos.z = ((float)(rand() % 100) - 50.0f);

		D3DXVECTOR3 nor = vecPos - VECTOR3_NULL;
		D3DXVec3Normalize(&nor, &nor);
		m_move = nor * 3.0f;
	}

	SetPos(pos);
}