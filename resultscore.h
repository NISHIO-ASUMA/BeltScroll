//========================================
//
// リザルト用スコア処理 [ resultscore.h ]
// Author: Asuma Nishio
//
//========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************
// 前方宣言
//**********************
class CNumber;

//********************************
// リザルト用スコアクラスを定義
//********************************
class CResultScore : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void LoadAll(void);
	void LoadGameScore(void);
	void LoadBounsScore(void);
	void MassLastScore(const int nGameScore, const int nBounsScore);

	// 静的メンバ関数
	static CResultScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	static constexpr int RESULT_SCORE = 8; // 表示桁数の定数値

	CNumber* m_pNumber[RESULT_SCORE];	// ナンバー配列
	D3DXVECTOR3 m_pos;			// 座標
	float m_fWidth;				// 横幅
	float m_fHeight;			// 高さ

	int m_nLoadScore;			// 読み取ったスコア
	int m_nBounsScore;			// ボーナススコア
	int m_nMassAllScore;			// 合計のスコア

	int m_nLoadScoreTime;		// ゲームスコアになる目的の時間
	int m_nBonusScoreTime;		// ボーナススコアになる目的の時間
	int m_nAllScoreTime;		// 合計スコアになる目的の時間

};

