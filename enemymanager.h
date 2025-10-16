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
	int m_nCount; // �o���J�E���g
};