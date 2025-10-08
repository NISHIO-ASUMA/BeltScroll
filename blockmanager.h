//=====================================
//
// �u���b�N�Ǘ����� [ blockmanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BLOCKMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _BLOCKMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include <vector>
#include "block.h"

//***************************
// �Ǘ��N���X���`
//***************************
class CBlockManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBlockManager();
	~CBlockManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static CBlock* CreateManagerBlock(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scale,const char * pModelName);

private:
	void LoadJsonScript(const char* jsonName); 	// �ǂݍ���

	static std::vector<CBlock*>m_block;	// ���I�z��
};

#endif