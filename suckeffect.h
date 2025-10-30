//====================================
//
// �z�����݃G�t�F�N�g���� [ suckeffect.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _SUCKEFFECT_H_ // ���̃}�N����`������ĂȂ�������
#define _SUCKEFFECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//*************************************************
// �G�t�F�N�g�N���X���`
//*************************************************
class CSuckEffect : public CBillboard
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSuckEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CSuckEffect();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetLife(int nLife) { m_nLife = nLife; }

	// �Q�b�^�[
	int GetLife(void) { return m_nLife; }

	// �ÓI�����o�֐�
	static CSuckEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	D3DXVECTOR3 m_targetPos;			// �ڕW�̈ʒu
	int m_nLife;						// �̗�
	float m_fRadius;					// ���a
	D3DXVECTOR3 m_move;					// �ړ���
};

#endif
