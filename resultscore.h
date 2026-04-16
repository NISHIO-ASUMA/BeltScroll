//=========================================================
//
// リザルト用スコア処理 [ resultscore.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "object.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CNumber;

//*********************************************************
// リザルト用スコアクラスを定義
//*********************************************************
class CResultScore : public CObject
{
public:

	//****************************
	// 種類定義
	//****************************
	enum SCORETYPE
	{
		SCORE_GAME,		// ゲームスコア
		SCORE_BONUS,	// ボーナススコア
		SCORE_ALL,		// 合計スコア
		SCORE_MAX
	};

	// コンストラクタ・デストラクタ
	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void UpdateGameScore(void);
	void UpdateBounsScore(void);
	void UpdateLastScore(void);
	void WriteScore(void);

	int GetScoreUpTimer(void) {return m_nTimer; }

	void SetGameScore(int nResultValue) 
	{
		m_nStartScore = 0;				// 初期値
		m_nLoadScore = nResultValue; // 目的地
		m_nCurrentScore = 0;

		m_nTimer = 0;
		m_nDuration = 180; // 3秒掛けて目的の値に
	}

	void SetBonusScore(int nResultValue)
	{
		m_nStartScore = 0;				// 初期値
		m_nBounsScore = nResultValue; 
		m_nCurrentScore = 0;

		m_nTimer = 0;
		m_nDuration = 180; // 3秒掛けて目的の値に
	}

	void SetAllScore(int nResultValue, int nResultValue1) 
	{ 
		m_nStartScore = 0;				// 初期値
		m_nMassAllScore = nResultValue + nResultValue1; 
		m_nCurrentScore = 0;

		m_nTimer = 0;
		m_nDuration = 180; // 3秒掛けて目的の値に
	}

	// 静的メンバ関数
	static CResultScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType);

private:

	static constexpr int RESULT_SCORE = 8; // 表示桁数の定数値

	CNumber* m_pNumber[RESULT_SCORE];	// ナンバー配列
	D3DXVECTOR3 m_pos;			// 座標

	float m_fWidth;				// 横幅
	float m_fHeight;			// 高さ
	int m_nLoadScore;			// 読み取ったスコア
	int m_nBounsScore;			// ボーナススコア
	int m_nMassAllScore;		// 合計のスコア
	int m_nCurrentScore;		// 今の表示スコア
	int m_nStartScore;			// 開始時のスコア
	int m_nTargetScore;			// ゴールのスコア
	int m_nTimer;				// 経過フレーム
	int m_nDuration;			// 目的の時間
	int nType;					// 種類
};

