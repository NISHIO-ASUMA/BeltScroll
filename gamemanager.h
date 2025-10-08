//======================================================
//
// �Q�[���V�[���I�u�W�F�N�g�Ǘ����� [ gamemanager.h ]
// Author: Asuma Nishio
//
//======================================================

#ifndef _GAMEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _GAMEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �Q�[���Ǘ��N���X���`
//**************************
class CGameManager
{
public:
	// �f�X�g���N�^
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CGameManager* GetInstance(void);

private:
	CGameManager() {}
	static CGameManager* m_pInstance; 	// �V���O���g���ϐ�
};

#endif