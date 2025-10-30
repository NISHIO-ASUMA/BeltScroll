//=============================================
//
// �z�����݃p�[�e�B�N������ [ suckParticle.h ]
// Author: Soichiro Sasaki
//=============================================

#ifndef _SUCKPARTICLE_H_ // ���̃}�N����`������ĂȂ�������
#define _SUCKPARTICLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include <vector>

//*********************
// �O���錾
//*********************
class CSuckEffect;

//**************************
// �p�[�e�B�N���N���X���`
//**************************
class CSuckParticle : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSuckParticle(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CSuckParticle();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CSuckParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos,D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife);

private:
	std::vector<CSuckEffect*> m_pEffect; // �G�t�F�N�g�z��

	D3DXVECTOR3 m_pos;	// ���W
	D3DXVECTOR3 m_targetPos;	// �ڕW�̍��W
	D3DXCOLOR m_col;	// �F
	int m_nMaxParticle; // �ő吔
	int m_nLife;		// ����
	int m_nLength;		// ��U���鋗��
	int m_nRadius;		// ���̑傫��

};

#endif