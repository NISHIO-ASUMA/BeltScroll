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
class CShadowS;
class CSphereCollider;
class CSphereSphereCollision;

//******************************
// �G�N���X���`
//******************************
class CEnemy : public CObjectX
{
public:
	//***************************
	// ��ނ̗񋓌^
	//***************************
	enum TYPE
	{
		TYPE_NONE,			// ����
		TYPE_LIGHTTRUSH,	// �y��
		TYPE_HEAVYTRUSH,	// �d��
		TYPE_ROLLTRUSH,		// �]����
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEnemy();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CSphereCollider * pOtherCollider);

	// �ÓI�����o�֐�
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// �Z�b�^�[
	void SetType(int Type) { m_TrushType = Type; }
	void AddBlow(const D3DXVECTOR3 Vec) { m_move += Vec; }
	void SetBlow(bool isFlags) { m_isBlow = isFlags; }

	// �Q�b�^�[
	int GetType(void) { return m_TrushType; }
	CSphereCollider* GetCollider(void) { return m_pCollider; }

private:
	D3DXVECTOR3 m_move;		// �ړ���
	CShadowS* m_pShadowS;	// �X�e���V���V���h�E
	int m_TrushType;		// �S�~�̎��
	bool m_isBlow;			// ������΂����L����
	CSphereCollider* m_pCollider; // �R���C�_�[
};

