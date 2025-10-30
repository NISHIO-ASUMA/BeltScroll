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
#include <iostream>
#include <sstream>

//==============================
// �R���X�g���N�^
//==============================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nCount = NULL;
	m_pEnemys.clear();
	m_EnemyData.clear();
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
	if (FAILED(pManager->Init())) return nullptr;

	return pManager;
}
//==============================
// ����������
//==============================
HRESULT CEnemyManager::Init(void)
{
	// �ǂݍ���
	CEnemyManager::LoadFile();

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
	m_EnemyData.clear();
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
	std::ifstream openfile("data/SCRIPT/EnemySystem.txt");
	if (!openfile)
	{
		MessageBox(GetActiveWindow(), "�t�@�C����������܂���", "data/SCRIPT/EnemySystem.txt", MB_OK);
		return;
	}

	std::string line;
	int nNumEnemy = 0;
	bool inBlock = false;

	// �z�񏉊���
	ENEMYDATA current{};
	m_EnemyData.clear();

	//==============================
	// �t�@�C����1�s�����
	//==============================
	while (std::getline(openfile, line))
	{
		// �R�����g����
		if (line.find('#') != std::string::npos)
			line = line.substr(0, line.find('#'));

		// ��s�X�L�b�v
		if (line.empty())
			continue;
		
		// �ǂݍ��ރ��C��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_ENEMY")
		{
			std::string eq;
			iss >> eq >> nNumEnemy;

			// �T�C�Y�m��
			m_EnemyData.reserve(nNumEnemy);
		}
		else if (token == "START")
		{
			inBlock = true;
			current = ENEMYDATA(); // �\���̏�����
		}
		else if (token == "END")
		{
			// ���X�g�֊i�[
			inBlock = false;
			m_EnemyData.push_back(current);
		}
		else if (token == "POS" && inBlock)
		{
			std::string eq; float x, y, z;

			iss >> eq >> x >> y >> z;

			// ���W�ݒ�
			current.pos = D3DXVECTOR3(x, y, z);
		}
		else if (token == "ROT" && inBlock)
		{
			std::string eq; 
			float x, y, z;

			iss >> eq >> x >> y >> z;

			// �p�x�ݒ�
			current.rot = D3DXVECTOR3(x, y, z);
		}
		else if (token == "TYPE" && inBlock)
		{
			std::string eq; 
			int type;
			
			iss >> eq >> type;

			// ��ސݒ�
			current.nType = type;
		}
		else if (token == "FILEPATH" && inBlock)
		{
			std::string eq, path;
			iss >> eq >> path;

			// ���f���p�X�ݒ�
			current.Modelname = path;
		}
		else if (token == "END_FILE")
		{
			break;
		}
	}

	// �t�@�C�������
	openfile.close();

	//==============================
	// ���ۂɓG���o��������
	//==============================
	for (const auto& data : m_EnemyData)
	{
		// �ǂݎ�����f�[�^����쐬
		CEnemy* pEnemy = CEnemy::Create
		(
			data.pos,
			data.rot,
			data.Modelname.c_str(),
			data.nType
		);

		// ���I�z��ɒǉ�
		if (pEnemy)
			m_pEnemys.push_back(pEnemy);
	}
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