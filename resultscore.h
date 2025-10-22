//========================================
//
// ���U���g�p�X�R�A���� [ resultscore.h ]
// Author: Asuma Nishio
//
//========================================

//**********************
// �C���N���[�h�K�[�h
//**********************
#pragma once

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************
// �O���錾
//**********************
class CNumber;

//********************************
// ���U���g�p�X�R�A�N���X���`
//********************************
class CResultScore : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	// �ÓI�����o�֐�
	static CResultScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	static constexpr int RESULT_SCORE = 8; // �\�������̒萔�l

	CNumber* m_pNumber[RESULT_SCORE];	// �i���o�[�z��
	D3DXVECTOR3 m_pos;			// ���W
	float m_fWidth;				// ����
	float m_fHeight;			// ����
	int m_nLoadScore;			// �ǂݎ�����X�R�A
};

