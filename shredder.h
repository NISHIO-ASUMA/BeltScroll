//=====================================
//
// �V�����b�_�[���� [ shredder.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//***************************
// �V�����b�_�[�N���X���`
//***************************
class CShredder : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CShredder(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CShredder();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CShredder* Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_move; // �ړ���
};