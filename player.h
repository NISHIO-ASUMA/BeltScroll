//====================================
//
// �v���C���[���� [ player.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PLAYER_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// �O���錾
//**********************
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;
class CAABBCollider;
class CSphereCollider;

//*************************
// �v���C���[�N���X���`
//*************************
class CPlayer : public CObject
{
public:
	//***********************************
	// �v���C���[���s�����[�V�����񋓌^
	//***********************************
	enum PLAYERMOTION
	{
		PLAYERMOTION_NEUTRAL,		// �j���[�g����
		PLAYERMOTION_MOVE,			// �ړ�
		PLAYERMOTION_ATTACK,		// �U��
		PLAYERMOTION_JUMP,			// �W�����v
		PLAYERMOTION_LANDING,		// ���n
		PLAYERMOTION_BLOWOFF,		// �_���[�W
		PLAYERMOTION_MOVEATTACK,	// �ړ����Ȃ���̃u�����[���[�V����
		PLAYERMOTION_MAX
	};

	//***********************************
	// �u�����[���[�h�񋓌^
	//***********************************
	enum BLOWER
	{
		BLOWER_SMALLPOW,
		BLOWER_MIDIUMPOW,
		BLOWER_MAXPOW,
		BLOWER_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CPlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeState(CPlayerStateBase* pNewState,int Id); // �X�e�[�g�ύX
	void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad); // �ʏ�U���X�V�֐�
	void UpdateMove(CInputKeyboard* pInputKeyboard, CJoyPad* pPad);					  // �ړ��X�V�֐�
	void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);
	void StartJump(void);
	void HitDamage(int nDamage);
	void EnemyBlow(void);
	bool Collision(CSphereCollider * pOther);

	// �Z�b�^�[
	void SetRotDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	void SetJump(bool isJump) { m_isJump = isJump; }
	void SetLanding(bool isLanding) { m_isLanding = isLanding; }
	void AddMove(void) { m_pos += m_move; }
	void SetValue(float fValue) { m_fValue = fValue; }
	void JumpMove(void) { m_move.y = m_fValue; }
	void SetBlower(int nType);
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// ���݂̍��W���擾
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }	// �ߋ��̍��W���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// ���݂̊p�x���擾
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }	// �ړI�p���擾
	PLAYERMOTION GetNowMotion(void) const;

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	CMotion* GetMotion(void) { return m_pMotion; }
	CStateMachine* GetStateMachine() { return m_pStateMachine; }	// �v���C���[�̃X�e�[�g�}�V�����擾
	CModel** GetModel(void) { return m_apModel; }
	int GetBlowType() const { return static_cast<int>(m_blower); }

	// �t���O�����g�֐�
	bool IsJumping() { return m_isJump; } 	// �W�����v��Ԃ̊m�F
	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isLanding(void) { return m_isJump; }
	bool GetLanding(void) { return m_isLanding; }
	bool GetIsAttack(void) { return m_isAttack; }

	// �ÓI�����o�֐�
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,const char* pFilename); // ��������
	static bool IsDeath(void) { return m_isDeath; }

private:
	static inline constexpr int MAX_MODEL = 16; // �v���C���[�Ŏg�����f���̐�

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;  // �ړI�p

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_posOld;	// �ߋ��̍��W���
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_Scal;		// �g�嗦
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[MAX_MODEL];	// �g�����f���̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����̃|�C���^
	CShadowS* m_pShadowS;			// �X�e���V���V���h�E�N���X�|�C���^
	CStateMachine* m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^
	CSphereCollider* m_pSphereCollider; // ���̃R���C�_�[

	int m_blower;			// ���

	int m_nNumAll;			// ���f������
	int m_State;			// ��ԊǗ��J�E���^�[

	bool m_isLanding;		// ���n����
	bool m_isJump;			// �W�����v����
	bool m_isMoving;		// �ړ��L�[����
	bool m_isAttack;		// �U������

	float m_fAngle;			// ���݂̊p�x
	float m_fValue;			// ���Z��
	float m_fBlowerRange;	// �e���͈�
	float m_fBlowerPow;		// �u�����[�̋��x
	const char* m_pFilename; // �ǂݍ��ރt�@�C����

	static bool m_isDeath; // �ÓI
};

#endif