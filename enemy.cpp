//==================================================
//
// �G�̏��� [ enemy.cpp ]
// Author: Asuma Nishio
// 
//==================================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "enemy.h"
#include "shadow.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"
#include "game.h"
#include "shadowS.h"
#include "collider.h"
#include "collision.h"
#include "shreddermanager.h"
#include "shredder.h"
#include "score.h"
#include "confettieffect.h"
#include "confettiparticle.h"

//==============================
// �R���X�g���N�^
//==============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_move(VECTOR3_NULL),
m_pShadowS(nullptr),
m_isBlow(false),
m_TrushType(TYPE_NONE),
m_pCollider(nullptr)
{
	// �l�̃N���A
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName,int nType)
{
	// �C���X�^���X����
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// �l����
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);
	pEnemy->SetType(nType);

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

	// �X�e���V���V���h�E�̐���
	m_pShadowS = CShadowS::Create(D3DXVECTOR3(GetPos().x, 0.0f, GetPos().z), GetRot());

	// ���R���C�_�[����
	m_pCollider = CSphereCollider::Create(GetPos(), 85.0f);

	// �ړ��ʂ��Z�b�g
	m_move.x = 5.0f;
	m_move.z = 5.0f;

	return S_OK;
}
//==============================
// �I������
//==============================
void CEnemy::Uninit(void)
{
	// �R���C�_�[�̔j��
	delete m_pCollider;
	m_pCollider = nullptr;

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

	// �u�����[�̎�ގ擾
	int nBlowerType = pPlayer->GetBlowType();

	// �v���C���[�Ɍ������Ă��鏈��
	D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�ʒu�擾
	D3DXVECTOR3 dir = playerPos - NowPos;		// �v���C���[�ւ̃x�N�g��
	float dist = D3DXVec3Length(&dir);

	D3DXVec3Normalize(&dir, &dir);
	float speed = 1.5f; // �Ǐ]�X�s�[�h
	m_move += dir * speed;

	// ���݂̃u�����[�̎�ނɉ����Ĕ�ԓG���ǂ����𔻒f
	if (m_TrushType <= nBlowerType)
	{
		// �ȉ��܂��͓���
		float friction = 0.92f;
		m_move *= friction;
	}
	else
	{
		// ����ȏ�̓G
		float friction = 0.65f;
		m_move *= friction;
	}

	if (D3DXVec3Length(&m_move) < 0.0f)
	{
		m_isBlow = false;
		m_move = VECTOR3_NULL;
	}
	
	// ���W�̍X�V
	m_move.y -= 0.5f;
	NowPos += m_move;
	if (NowPos.y <= 0.0f) NowPos.y = 0.0f;

	// �R���C�_�[���W
	m_pCollider->SetPos(NowPos);

	// �����蔻�萶��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �R���C�_�[�擾 ( 2�̃V�����b�_�[������ )
		auto ShredderCol = CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt)->GetCollider();

		if (Collision(ShredderCol))
		{
			// �G�t�F�N�g����
			CConfettiParticle::Create(GetPos(), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 40, 150, 500, 40, -D3DX_PI * 0.5f);

			// ����
			this->Uninit();

			// �e������
			m_pShadowS->Uninit();
			
			return;
		}
	}

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	// ���W���Z�b�g
	SetPos(NowPos);

	// �X�e���V���X�V
	if (m_pShadowS)
	{
		m_pShadowS->SetPos(D3DXVECTOR3(GetPos().x, -2.0f, GetPos().z));
		m_pShadowS->SetRot(GetRot());
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
//==============================
// �����蔻�菈��
//==============================
bool CEnemy::Collision(CAABBCollider* pOtherCollider)
{
	// ���茋�ʂ�Ԃ�
	return CAABBSphereCollision::CollisionT(pOtherCollider, m_pCollider);
}