//=========================================
//
// ランキングスコア処理 [ rankingscore.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _RANKINGSCORE_H_ // このマクロ定義がされてなかったら
#define _RANKINGSCORE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************
// 前方宣言
//**********************
class CNumber;

//*******************************
// ランキングスコアのクラス定義
//*******************************
class CRankingScore : public CObject
{
public:

	// コンストラクタ・デストラクタ
	CRankingScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CRankingScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);

	// 静的メンバ関数
	static CRankingScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	static constexpr int MAX_DIGIT = 8; // 桁数の定数
	static constexpr int MAX_RANK = 5;	// 順位数の定数

	CNumber* m_apNumbers[MAX_RANK][MAX_DIGIT];	// 使う数字数のポインタ
	int m_RankData[MAX_RANK];					// 五位分の数値配列

	D3DXVECTOR3 m_pos;				// 位置
	float m_fWidth, m_fHeight;		// 幅、高さ
};

#endif