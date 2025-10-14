//=====================================
//
// ランキングスコア処理 [ rankingscore.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "number.h"

//*******************************
// ランキングスコアのクラス定義
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

    CNumber* m_apNumbers[MAX_DIGIT];				// 数字のポインタ
    D3DXVECTOR3 m_pos;                              // 位置
    int m_ScoreNum;							        // スコアの数字総数
    float m_fWidth, m_fHeight;                      // 幅、高さ
};

#endif // !_RANKINGSCORE_H_
