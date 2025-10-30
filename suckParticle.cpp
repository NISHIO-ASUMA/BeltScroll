//==================================================
//
// �z�����݃p�[�e�B�N������ [ suckParticle.h ]
// Author: Soichiro Sasaki
//
//==================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "suckParticle.h"
#include "manager.h"
#include "suckeffect.h"

//=====================================
// �I�[�o�[���[�h�R���X�g���N�^
//=====================================
CSuckParticle::CSuckParticle(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
}
//=====================================
// �f�X�g���N�^
//=====================================
CSuckParticle::~CSuckParticle()
{
	// ����
}
//=====================================
// ��������
//=====================================
CSuckParticle* CSuckParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife)
{
	// �p�[�e�B�N���̃|�C���^��錾
	CSuckParticle* pParticle = new CSuckParticle;

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
	pParticle->m_targetPos = targetPos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;

	// �|�C���^��Ԃ�
	return pParticle;
}
//=====================================
// ����������
//=====================================
HRESULT CSuckParticle::Init(void)
{
	// �z��N���A
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// �I������
//=====================================
void CSuckParticle::Uninit(void)
{
	// �z��N���A
	m_pEffect.clear();

	// �e�N���X�̔j��
	CObject::Release();
}
//=====================================
// �X�V����
//=====================================
void CSuckParticle::Update(void)
{
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;
	D3DXVECTOR3 targetPos = m_targetPos;

	for (int nCnt = 0; nCnt < m_nMaxParticle; nCnt++)
	{
		pos.x = pos.x + ((float)(rand() % 30) - 15.0f);
		pos.y = pos.y + ((float)(rand() % 60) - 30.0f);
		pos.z = pos.z + ((float)(rand() % 150) - 75.0f);

		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		float fRise = (float)(rand() % m_nLength) / 50.0f + 7.0f;

		// ����
		int nLife = ((rand() % m_nLife) + 10);

		// �p�[�e�B�N������
		CSuckEffect* pEffect = CSuckEffect::Create(pos, targetPos, col,VECTOR3_NULL, nLife, fRadius);

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
void CSuckParticle::Draw(void)
{
	// ����
}
