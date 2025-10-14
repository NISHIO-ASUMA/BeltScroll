//=====================================
//
// �u���b�N�Ǘ����� [ blockmanager.h ]
// Author: Asuma Nishio
//
//=====================================

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include "blockmanager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"

//***************************
// �ÓI�����o�ϐ�
//***************************
std::vector<CBlock*>CBlockManager::m_block = {}; // ���I�z��

//***************************
// �g�p���O���
//***************************
using json = nlohmann::json; // json�t�@�C���`�����g�p����

//===========================
// �R���X�g���N�^
//===========================
CBlockManager::CBlockManager()
{
	// �l�̃N���A
	m_block.clear();
}
//===========================
// �f�X�g���N�^
//===========================
CBlockManager::~CBlockManager()
{
	// ����
}
//===========================
// ����������
//===========================
HRESULT CBlockManager::Init(void)
{
	// �z���؂藣��
	m_block.clear();

	// json�J��
	LoadJsonScript("data/JSON/NewDataStage.json");

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===========================
// �I������
//===========================
void CBlockManager::Uninit(void)
{
	// �z��؂藣��
	m_block.clear();
}
//===========================
// �X�V����
//===========================
void CBlockManager::Update(void)
{

}
//===========================
// ��������
//===========================
CBlock* CBlockManager::CreateManagerBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, const char* pModelName)
{
	// �C���X�^���X����
	CBlock* pManagBlock = CBlock::Create(pos,rot,scale,pModelName);

	if (pManagBlock != nullptr)
	{
		// �z��ǉ�
		m_block.push_back(pManagBlock);
	}

	// �������ꂽ����Ԃ�
	return pManagBlock;
}
//===========================
// �ǂݍ��ݏ���
//===========================
void CBlockManager::LoadJsonScript(const char* jsonName)
{
	// �J���t�@�C��
	std::ifstream file(jsonName);

	// �J����������
	if (!file.is_open())
	{
		// ��O
		MessageBox(nullptr, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONERROR);

		// �I��
		return;
	}

	// json����擾����
	json j;
	file >> j;

	// �t�@�C�������
	file.close();

	// �����̃u���b�N������
	for (auto block : m_block)
	{
		if (block != nullptr)
		{
			// �u���b�N�̏I������
			block->Uninit();
		}
	}

	// ���I�z�����ɂ���
	m_block.clear();

	// SetObjects�̔z�����
	for (const auto& b : j["SetObjects"])
	{
		std::string filepath = b["filepath"];
		int idx = b["idx"];

		D3DXVECTOR3 pos(
			b["pos"][0],
			b["pos"][1],
			b["pos"][2]
		);
		D3DXVECTOR3 rot(
			b["rot"][0],
			b["rot"][1],
			b["rot"][2]
		);

		D3DXVECTOR3 size(
			b["scale"][0],
			b["scale"][1],
			b["scale"][2]
		);

		// �u���b�N����
		CBlock* block = CreateManagerBlock(pos, rot, size, filepath.c_str());
	}
}