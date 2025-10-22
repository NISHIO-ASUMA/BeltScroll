//=========================================
//
// �����L���O�X�R�A���� [ rankingscore.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _RANKINGSCORE_H_ // ���̃}�N����`������ĂȂ�������
#define _RANKINGSCORE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************
// �O���錾
//**********************
class CNumber;

//*******************************
// �����L���O�X�R�A�̃N���X��`
//*******************************
class CRankingScore : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRankingScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CRankingScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	// �ÓI�����o�֐�
	static CRankingScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	static constexpr int MAX_DIGIT = 8; // �����̒萔
	static constexpr int MAX_RANK = 5;	// ���ʐ��̒萔

	CNumber* m_apNumbers[MAX_RANK][MAX_DIGIT];	// �g���������̃|�C���^
	int m_RankData[MAX_RANK];					// �܈ʕ��̐��l�z��

	D3DXVECTOR3 m_pos;				// �ʒu
	float m_fWidth, m_fHeight;		// ���A����
};

#endif