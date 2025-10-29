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
// �O���錾
//***************************
class CAABBCollider;

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
	bool Collision(CAABBCollider* pCollider, D3DXVECTOR3* OutPos);

	static int GetAll(void) { return static_cast<int>(m_block.size()); }
	static CBlock* GetBlock(const int nIdx) { return m_block[nIdx]; }
	static std::vector <CBlock*> GetInfo() { return m_block; }

	// �ÓI�����o�֐�
	static CBlock* CreateManagerBlock(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scale,const char * pModelName);

private:
	void LoadJsonScript(const char* jsonName); 	// �ǂݍ���

	static std::vector<CBlock*>m_block;	// ���I�z��
};

#endif