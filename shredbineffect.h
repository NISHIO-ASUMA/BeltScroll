//====================================
//
// �V�����b�h�r���G�t�F�N�g���� [ shredbineffect.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _SHREDBINEFFECT_H_ // ���̃}�N����`������ĂȂ�������
#define _SHREDBINEFFECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//*************************************************
// �G�t�F�N�g�N���X���`
//*************************************************
class CShredbinEffect : public CBillboard
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CShredbinEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CShredbinEffect();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);

	// �Q�b�^�[
	static int GetNumAll(void) { return m_nNumAll; }

	// �ÓI�����o�֐�
	static CShredbinEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col,float fRadius);

private:
	static int m_nNumAll;
	D3DXVECTOR3 m_oldPos;
	D3DXVECTOR3 m_offsetPos;
	D3DXVECTOR3 m_size;
	int m_nIdx;							// �̗�
	float m_fRadius;					// ���a
	D3DXVECTOR3 m_move;					// �ړ���
};

#endif
