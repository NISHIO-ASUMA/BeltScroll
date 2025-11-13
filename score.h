//===================================
//
// スコア処理 [ score.h ]
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

//******************************
// 前方宣言
//******************************
class CNumber;

//******************************
// スコアクラスを定義
//******************************
class CScore : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CScore* Create(D3DXVECTOR3 pos,float fWidth,float fHeight);
	static void Save(void);
	static void ClearScore(void) { m_nScore = NULL; }
	static void Add(int nValue) 
	{
		m_nScore += nValue; 
	}

private:
	static constexpr int SCORE_NUM = 8; // 表示桁数の定数
	static int m_nScore; // 格納スコア

	CNumber* m_pNumber[SCORE_NUM];	// ナンバー配列
	D3DXVECTOR3 m_pos;				// 座標
	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
};

