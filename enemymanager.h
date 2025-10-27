//===================================
//
// �G�Ǘ����� [ enemymanager.h ]
// Author: Asuma Nishio
//
//===================================

//******************************
// �C���N���[�h�K�[�h
//******************************
#pragma once

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include <vector>

//******************************
// �O���錾
//******************************
class CEnemy;

//******************************
// �G�Ǘ��N���X���`
//******************************
class CEnemyManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyManager();
	~CEnemyManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static CEnemyManager* Create(void);

private:

	void LoadFile(void);				   // �t�@�C���ǂݍ��݊֐�
	void LoadSplit(const char* pFileName); // �����ǂݍ���

	int m_nCount; // �o���J�E���g

	std::vector<CEnemy*>m_pEnemys;		// �G�̓��I�z��
};