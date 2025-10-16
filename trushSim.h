//=====================================
//
// �����̂��ݏ��� [ trushSim.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _TRUSHSIM_H_ // ���̃}�N����`������ĂȂ�������
#define _TRUSHSIM_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

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
class CTrushSim : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTrushSim(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CTrushSim();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Controll(void);
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding);

	// �ÓI�����o�֐�
	static CTrushSim* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName);

private:
	D3DXVECTOR3 m_posOld;
	static constexpr float BLOCKHALF = 0.5f;	// �n�[�t�T�C�Y�̌Œ�l
};

#endif