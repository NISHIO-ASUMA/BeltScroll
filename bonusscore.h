//===================================
//
// ボーナススコア処理 [ bonusscore.h ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードガード
//******************************
#pragma once

//******************************
// インクルードファイル
//******************************
#include "object.h"
#include "number.h"

//******************************
// ボーナススコアクラスを定義
//******************************
class CBonusScore : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CBonusScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBonusScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBonusScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static void Save(void);
	static void ClearScore(void) { m_nScore = NULL; }
	static void Add(int nValue) { m_nScore += nValue; }

private:
	static constexpr int SCORE_NUM = 8; // 表示桁数の定数
	static int m_nScore; // 格納スコア

	CNumber* m_pNumber[SCORE_NUM];	// ナンバー配列
	D3DXVECTOR3 m_pos;				// 座標
	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
};