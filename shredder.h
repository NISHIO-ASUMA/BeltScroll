//=====================================
//
// �V�����b�_�[���� [ shredder.h ]
// Author: Soichiro Sasaki
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

//**********************
// �O���錾
//**********************
class CAABBCollider;
class CModel;

//***************************
// �V�����b�_�[�N���X���`
//***************************
class CShredder : public CObject
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
	void InitModel(void);
	void UpdateModel(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetPosZ(float posZ);
	CAABBCollider* GetCollider(void) { return m_pAABB; }

	// �ÓI�����o�֐�
	static CShredder* Create(D3DXVECTOR3 pos,int nType);

private:
	static constexpr int nNumParts = 2;
	CModel* m_apModel[nNumParts];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
	D3DXVECTOR3 m_move; // �ړ���
	int m_nType;		// ���
	CAABBCollider* m_pAABB; // ��`�̃R���C�_�[
};