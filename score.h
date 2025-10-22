//===================================
//
// �X�R�A���� [ score.h ]
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
#include "object.h"

//******************************
// �O���錾
//******************************
class CNumber;

//******************************
// �X�R�A�N���X���`
//******************************
class CScore : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CScore* Create(D3DXVECTOR3 pos,float fWidth,float fHeight);
	static void Save(void);
	static void ClearScore(void) { m_nScore = NULL; }
	static void Add(int nValue) { m_nScore += nValue; }

private:
	static constexpr int SCORE_NUM = 8; // �\�������̒萔
	static int m_nScore; // �i�[�X�R�A

	CNumber* m_pNumber[SCORE_NUM];	// �i���o�[�z��
	D3DXVECTOR3 m_pos;				// ���W
	float m_fWidth;					// ����
	float m_fHeight;				// ����
};

