//=============================================
//
// �s�k�v���C���[���� [ loseplayer.h ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�K�[�h
//**************************
#pragma once

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "object.h"

//**********************
// �O���錾
//**********************
class CInputKeyboard;
class CJoyPad;
class CShadowS;
class CModel;
class CMotion;

//*******************************
// �����L�����N�^�[�N���X���`
//*******************************
class CLosePlayer : public CObject
{
public:
	//**************************
	// ���[�V�����̎��
	//**************************
	enum LOSEMOTION
	{
		LOSEMOTION_NEUTRAL, // �����l
		LOSEMOTION_ACTION,	// �A�N�V����
		LOSEMOTION_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CLosePlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CLosePlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����֐�
	static CLosePlayer* Create(D3DXVECTOR3 pos);

private:

	static inline constexpr int LOSE_MODEL = 16; // �v���C���[�Ŏg�����f���̐�

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_rotDest;  // �ړI�p
	D3DXVECTOR3 m_Scal;		// �g�嗦
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[LOSE_MODEL];	// �g�����f���̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����̃|�C���^
	CShadowS* m_pShadowS;			// �X�e���V���V���h�E�N���X�|�C���^

	const char* m_pFilename; // �ǂݍ��ރt�@�C����
};

