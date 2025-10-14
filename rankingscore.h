//=====================================
//
// �����L���O�X�R�A���� [ rankingscore.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "number.h"

//*******************************
// �����L���O�X�R�A�̃N���X��`
//*******************************
class CRankingScore : public CObject
{
public:
    CRankingScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
    ~CRankingScore();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    int Load(const char* pFileName);

    static CRankingScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
    static constexpr int MAX_DIGIT = 8;

    CNumber* m_apNumbers[MAX_DIGIT];				// �����̃|�C���^
    D3DXVECTOR3 m_pos;                              // �ʒu
    int m_ScoreNum;							        // �X�R�A�̐�������
    float m_fWidth, m_fHeight;                      // ���A����
};

#endif // !_RANKINGSCORE_H_
