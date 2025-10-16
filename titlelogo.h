//=====================================
//
// �^�C�g�����S���� [ titlelogo.h ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�K�[�h
//****************************
#pragma once

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "object2D.h"

//****************************
// �^�C�g�����S�N���X���`
//****************************
class CTitleLogo : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleLogo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleLogo();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTitleLogo* Create(D3DXVECTOR3 pos);

private:

};

