//===================================
//
// �S�[���n�_���� [ goal.h ]
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
#include "objectX.h"

//***********************************
// �S�[���|�C���g�N���X���`
//***********************************
class CGoal : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CGoal(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGoal();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CheckPos(D3DXVECTOR3 pos);

	// �ÓI�����o�֐�
	static CGoal* Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_DestPos; // �ړI�n���W
};