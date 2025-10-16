//===================================
//
// �G�Ǘ����� [ enemymanager.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "enemymanager.h"
#include "enemy.h"

//==============================
// �R���X�g���N�^
//==============================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nCount = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CEnemyManager::~CEnemyManager()
{
	// ����
}
//==============================
// ��������
//==============================
CEnemyManager* CEnemyManager::Create(void)
{
	// �C���X�^���X����
	CEnemyManager* pManager = new CEnemyManager;
	if (pManager == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pManager->Init()))
	{
		return nullptr;
	}

	return pManager;
}
//==============================
// ����������
//==============================
HRESULT CEnemyManager::Init(void)
{
	// �����G����
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/enemy000.x");
	CEnemy::Create(D3DXVECTOR3(-550.0f, 0.0f, -550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/enemy000.x");

	// ����������
	return S_OK;
}
//==============================
// �I������
//==============================
void CEnemyManager::Uninit(void)
{
	// ���͖���
}
//==============================
// �X�V����
//==============================
void CEnemyManager::Update(void)
{
	// �̂��Ɏ��Ԃɂ���ďo�� �܂��� ��ʂ��Ƃɏo���G�������ŌĂяo��
}