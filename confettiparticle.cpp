//==================================================
//
// ������p�[�e�B�N������ [ confettiparticle.h ]
// Author: Soichiro Sasaki
//
//==================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "confettiparticle.h"
#include "manager.h"
#include "confettieffect.h"

//=====================================
// �I�[�o�[���[�h�R���X�g���N�^
//=====================================
CConfettiParticle::CConfettiParticle(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
	m_fAngle = NULL;
}
//=====================================
// �f�X�g���N�^
//=====================================
CConfettiParticle::~CConfettiParticle()
{
	// ����
}
//=====================================
// ��������
//=====================================
CConfettiParticle* CConfettiParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife, float fAngle)
{
	// �p�[�e�B�N���̃|�C���^��錾
	CConfettiParticle* pParticle = new CConfettiParticle;

	// null��������
	if (pParticle == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pParticle->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pParticle->m_pos = pos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;
	pParticle->m_fAngle = fAngle;

	// �|�C���^��Ԃ�
	return pParticle;
}
//=====================================
// ����������
//=====================================
HRESULT CConfettiParticle::Init(void)
{
	// �z��N���A
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// �I������
//=====================================
void CConfettiParticle::Uninit(void)
{
	// �z��N���A
	m_pEffect.clear();

	// �e�N���X�̔j��
	CObject::Release();
}
//=====================================
// �X�V����
//=====================================
void CConfettiParticle::Update(void)
{
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;

	// �p�x
	float fHalfSpread = D3DXToRadian(30.0f);// ��`�̍L����

	for (int nCnt = 0; nCnt < m_nMaxParticle; nCnt++)
	{
		// �v���C���[���ʂ𒆐S�� �}30���͈̔͂Ŋp�x������
		float fAngle = m_fAngle + ((float)rand() / RAND_MAX * 2.0f - 1.0f) * fHalfSpread;

		// 
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		float fRise = (float)(rand() % m_nLength) / 50.0f + 7.0f;

		// �ړ�����
		D3DXVECTOR3 Move;
		Move.x = -sinf(fAngle) * fRadius;  // 
		Move.z = -cosf(fAngle) * fRadius;  //
		Move.y = fRise;

		// ����
		int nLife = ((rand() % m_nLife) + 10);

		// �p�[�e�B�N������
		CConfettiEffect* pEffect = CConfettiEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
			m_pEffect.push_back(pEffect);
		else
			break;
	}

	// �j��
	Uninit();
}
//=====================================
// �`�揈��
//=====================================
void CConfettiParticle::Draw(void)
{
	// ����
}
