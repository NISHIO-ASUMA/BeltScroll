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
class CEnemyManager;
class CTrushSim;
class CShredderManager;
class CGoal;

//**************************
// �C���N���[�h�t�@�C��
//**************************
#include <memory>

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
	CTrushSim* GetTrush(void) { return m_pTrushSim; }
	CGoal* GetGoal(void) { return m_pGoal; }
	CShredderManager* GetShredderM(void) { return m_pShredderManaher; }
	CBlockManager* GetBlockManager(void) { return m_pBlockManager; }
	CEnemyManager* GetEnemyManager(void) { return m_pEnemyManager.get(); }

private:
	std::unique_ptr<CEnemyManager>m_pEnemyManager; // �G�Ǘ�
	CBlockManager* m_pBlockManager; // �u���b�N�}�l�[�W���[
	CPlayer* m_pPlayer;				// �v���C���[
	CTrushSim* m_pTrushSim;			// ����
	CShredderManager* m_pShredderManaher;// �V�����b�_�[�}�l�[�W���[
	CGoal* m_pGoal;					// �S�[���N���X
};

#endif