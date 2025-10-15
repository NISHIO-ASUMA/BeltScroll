//===================================
//
// �G�̏��� [ enemy.h ]
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
#include "object.h"
#include "model.h"
#include "motion.h"

//******************************
// �O���錾
//******************************
class CShadow;

//******************************
// �G�N���X���`
//******************************
class CEnemy : public CObject
{
public:
	//***********************************
	// �G���s�����[�V�����񋓌^
	//***********************************
	enum ENEMYMOTION
	{
		ENEMYMOTION_NEUTRAL,	// �j���[�g����
		ENEMYMOTION_MAX
	};

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	static constexpr int ENEMY_MODEL = 1;

	D3DXVECTOR3 m_pos; // ���W
	D3DXVECTOR3 m_Oldpos; // �ߋ����W
	D3DXVECTOR3 m_rot; // �p�x
	D3DXVECTOR3 m_scale; // �g�嗦
	D3DXVECTOR3 m_move; // �ړ���
	D3DXMATRIX m_mtxworld; // ���[���h�}�g���b�N�X

	CModel* m_pModel[ENEMY_MODEL]; // ���f���|�C���^
	CMotion* m_pMotion; // ���[�V�����|�C���^
	CShadow* m_pShadow; // �V���h�E
	const char* m_pScriptName; // ���[�V�����t�@�C����
};

