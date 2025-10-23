//=============================================
//
// �����v���C���[���� [ winplayer.h ]
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
class CWinPlayer : public CObject
{
public:
	//**************************
	// ���[�V�����̎��
	//**************************
	enum WINMOTION
	{
		WINMOTION_NEUTRAL, // �����l
		WINMOTION_ACTION,  // �A�N�V����
		WINMOTION_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CWinPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CWinPlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�����֐�
	static CWinPlayer* Create(D3DXVECTOR3 pos);

private:
	static inline constexpr int WIN_MODEL = 16; // �v���C���[�Ŏg�����f���̐�

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_rotDest;  // �ړI�p
	D3DXVECTOR3 m_Scal;		// �g�嗦
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[WIN_MODEL];	// �g�����f���̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����̃|�C���^
	CShadowS* m_pShadowS;			// �X�e���V���V���h�E�N���X�|�C���^

	const char* m_pFilename; // �ǂݍ��ރt�@�C����
};

