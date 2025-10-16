//===================================
//
// �G�̏��� [ enemy.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "enemy.h"
#include "shadow.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"
#include "game.h"

//==============================
// �R���X�g���N�^
//==============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_pShadow = nullptr;

	m_isBlow = false;
}
//==============================
// �f�X�g���N�^
//==============================
CEnemy::~CEnemy()
{
	// ����
}
//==============================
// ��������
//==============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName)
{
	// �C���X�^���X����
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// �l����
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);

	// ���������s��
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�C���X�^���X��Ԃ�
	return pEnemy;
}
//==============================
// ����������
//==============================
HRESULT CEnemy::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_ENEMY);

	// �V���h�E����
	m_pShadow = CShadow::Create(D3DXVECTOR3(GetPos().x,2.0f,GetPos().z), GetRot());

	// �ړ��ʂ��Z�b�g
	m_move.x = 3.0f;
	m_move.z = 3.0f;

	return S_OK;
}
//==============================
// �I������
//==============================
void CEnemy::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//==============================
// �X�V����
//==============================
void CEnemy::Update(void)
{
	// �v���C���[�擾
	CPlayer* pPlayer = CGame::GetGameManager()->GetPlayer();
	if (pPlayer == nullptr) return;

	// ���W�擾
	D3DXVECTOR3 NowPos = GetPos();

	// �v���C���[�Ɍ������Ă��鏈��
	D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�ʒu�擾
	D3DXVECTOR3 dir = playerPos - NowPos;		// �v���C���[�ւ̃x�N�g��
	float dist = D3DXVec3Length(&dir);			// ����

	D3DXVec3Normalize(&dir, &dir);			// ���K��
	float speed = 1.0f;						// �Ǐ]�X�s�[�h
	m_move += dir * speed;					// �ړ��x�N�g���ɉ��Z

	// ������΂����L���̎�
	if (m_isBlow)
	{
		// ���C�W�����v�Z����
		m_move *= 0.9f; // ����

		if (D3DXVec3Length(&m_move) < 0.05f)
		{
			m_isBlow = false;
			m_move = VECTOR3_NULL;
		}
	}

	m_move.y -= 0.5f;

	// �ʒu�X�V
	NowPos += m_move;
	
	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	if (NowPos.y <= 0.0f)
	{
		NowPos.y = 0.0f;
	}

	// ���W�Z�b�g
	SetPos(NowPos);

	 // �X�e���V���V���h�E������
	if (m_pShadow)
	{
		// �I�u�W�F�N�g�ݒ�
		m_pShadow->SetPos(D3DXVECTOR3(GetPos().x, 2.0f, GetPos().z));
		m_pShadow->SetRot(GetRot());
	}
}
//==============================
// �`�揈��
//==============================
void CEnemy::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}