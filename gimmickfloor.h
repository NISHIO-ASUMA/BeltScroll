//=====================================
//
// ���������� [ gimmickfloor.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _GIMMICKFLOOR_H_ // ���̃}�N����`������ĂȂ�������
#define _GIMMICKFLOOR_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//**********************
// �O���錾
//**********************
class CObject;

//**********************
// �������N���X���`
//**********************
class CGimmickFloor : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CGimmickFloor(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGimmickFloor();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(void);
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding);

	// �ÓI�����o�֐�
	static CGimmickFloor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName);

private:
	float m_fMoveCnt;		// �u���b�N�𓮂����J�E���g
	static constexpr float COUNTSPEED = 0.01f;	// 1�t���[���̃J�E���g��
	static constexpr float BLOCKHALF = 0.5f;	// �n�[�t�T�C�Y�̌Œ�l
};

#endif