//====================================
//
// �u�����[UI���� [ blowerui.h ]
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
// �C���N���[�h�t�@�C���錾
//****************************
class CBlowerUi : public CObject2D
{
public:
	//***************************
	// ��ނ��`
	//***************************
	enum TYPE
	{
		TYPE_NONE,
		TYPE_SMALL,
		TYPE_MIDIUM,
		TYPE_FULL,
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBlowerUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBlowerUi();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBlowerUi* Create(D3DXVECTOR3 pos, const char* pFileName);

private:

};

