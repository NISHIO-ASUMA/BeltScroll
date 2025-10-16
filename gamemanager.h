//======================================================
//
// �Q�[���V�[���I�u�W�F�N�g�Ǘ����� [ gamemanager.h ]
// Author: Asuma Nishio
//
//======================================================

#ifndef _GAMEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _GAMEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �O���錾
//**************************
class CBlockManager;
class CPlayer;

//**************************
// �Q�[���Ǘ��N���X���`
//**************************
class CGameManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CGameManager();
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CPlayer* GetPlayer(void) { return m_pPlayer; }

private:
	CBlockManager* m_pBlockManager; // �u���b�N�}�l�[�W���[
	CPlayer* m_pPlayer;				// �v���C���[
};

#endif