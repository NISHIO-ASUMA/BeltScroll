//===========================================
//
// ������G�t�F�N�g���� [ confettieffect.cpp ]
// Author: Soichiro Sasaki
//
//===========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "confettieffect.h"
#include "manager.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CConfettiEffect::CConfettiEffect(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CConfettiEffect::~CConfettiEffect()
{
	// ����
}
//===============================
// ��������
//===============================
CConfettiEffect* CConfettiEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// �G�t�F�N�g�|�C���^
	CConfettiEffect* pEffect = new CConfettiEffect;

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
	pEffect->SetTexture("confetti.jpg");

	// ���a����
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->SetLife(nLife);

	// �G�t�F�N�g�|�C���^��Ԃ�
	return pEffect;
}
//===============================
// ����������
//===============================
HRESULT CConfettiEffect::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	return S_OK;
}
//===============================
// �I������
//===============================
void CConfettiEffect::Uninit(void)
{
	// �e�N���X�̏I��
	CBillboard::Uninit();
}
//===============================
// �X�V����
//===============================
void CConfettiEffect::Update(void)
{
	// ���W,�J���[�擾
	D3DXVECTOR3 Effectpos = GetPos();
	D3DXVECTOR3 Effectrot = GetRot();

	//�J���[�̐ݒ�
	D3DXCOLOR col = GetCol();

	// �I�u�W�F�N�g�X�V
	CBillboard::Update();

	// �ړ��ʂ̍X�V
	Effectpos += m_move;
	m_move.y -= 0.4f;

	// ���Z����l��ݒ�
	const float fDecPow = 0.005f;

	// ���a���f�N�������g
	m_fRadius -= fDecPow;

	// ���l������
	col.a -= fDecPow;

	Effectrot.z += 0.2f;

	// ���W���Z�b�g����
	SetPos(Effectpos);

	// �������Z�b�g����
	SetRot(Effectrot);

	// �J���[���Z�b�g
	SetCol(col);

	// 0�ȉ��Ȃ�
	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// �T�C�Y�Z�b�g
	SetSize(m_fRadius, m_fRadius);

	// �̗͂����炷
	m_nLife--;

	// 0�ȉ��̎�
	if (m_nLife <= NULL)
	{
		// �폜����
		Uninit();
	}
}
//===============================
// �`�揈��
//===============================
void CConfettiEffect::Draw(void)
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