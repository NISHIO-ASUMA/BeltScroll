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
#include <fstream>

//==============================
// �R���X�g���N�^
//==============================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nCount = NULL;
	m_pEnemys.clear();
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
	// �����G���� ( �̂��ɃX�N���v�g�ύX )
	CEnemy::Create(D3DXVECTOR3(00.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/obj/fish.x");
	CEnemy::Create(D3DXVECTOR3(-550.0f, 0.0f, -550.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(550.0f, 0.0f, 550.0f), VECTOR3_NULL, "data/MODEL/obj/kan.x");
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), VECTOR3_NULL, "data/MODEL/obj/fish.x");
	CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), VECTOR3_NULL, "data/MODEL/STAGEOBJ/Dunbel.x");
	CEnemy::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), VECTOR3_NULL, "data/MODEL/obj/kan.x");

	// ����������
	return S_OK;
}
//==============================
// �I������
//==============================
void CEnemyManager::Uninit(void)
{
	// �j��
	m_pEnemys.clear();
}
//==============================
// �X�V����
//==============================
void CEnemyManager::Update(void)
{
	// �̂��Ɏ��Ԃɂ���ďo�� �܂��� ��ʂ��Ƃɏo���G�������ŌĂяo��
}
//==============================
// �t�@�C���ǂݍ���
//==============================
void CEnemyManager::LoadFile(void)
{
	// �J���t�@�C�����Z�b�g
	std::ifstream openfile("data/SCRIPT/EnemySystem.txt");
	if (!openfile)
	{
		// ��O
		MessageBox(GetActiveWindow(), "�t�@�C����������܂���", "data/SCRIPT/EnemySystem.txt", MB_OK);
		return;
	}

	// �g�p�ϐ�

}
//==============================
// �����t�@�C���ǂݍ���
//==============================
void CEnemyManager::LoadSplit(const char* pFileName)
{
	// �J���t�@�C�����Z�b�g
	std::ifstream opensplit(pFileName);
	if (!opensplit)
	{
		// ��O
		MessageBox(GetActiveWindow(), "���̃t�@�C���p�X�͂���܂���", "�ǂݍ��݃G���[", MB_OK);
		return;
	}
}