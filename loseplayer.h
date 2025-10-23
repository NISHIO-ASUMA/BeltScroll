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

};

