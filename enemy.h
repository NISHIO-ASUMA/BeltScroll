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
#include "objectX.h"

//******************************
// �O���錾
//******************************
class CShadow;

//******************************
// �G�N���X���`
//******************************
class CEnemy : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEnemy();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// �Z�b�^�[
	void AddBlow(const D3DXVECTOR3 Vec) { m_move += Vec; }
	void SetBlow(bool isFlags) { m_isBlow = isFlags; }

private:
	D3DXVECTOR3 m_move; // �ړ���
	CShadow* m_pShadow; // �V���h�E

	bool m_isBlow;		// ������΂����L����
};

