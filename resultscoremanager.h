//=======================================================
//
// リザルト用スコア管理処理 [ resultscoremanager.h ]
// Author: Asuma Nishio
//
//=======================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// 前方宣言
//**********************
class CResultScore;

//**********************
// 管理クラスを定義
//**********************
class CResultScoreManager
{
public:

	// コンストラクタ・デストラクタ
	CResultScoreManager();
	~CResultScoreManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);

	CResultScore* GetIdx(const int nidx) { return m_pResultScore[nidx]; }

private:

	static constexpr int SCORELISTNUM = 3; // 配列の最大数

	//**********************
	// 定数格納構造体
	//**********************
	struct Config
	{
		static constexpr int GAME = 0; // ゲームスコアインデックス
		static constexpr int BONUS = 1; // ボーナススコアインデックス
		static constexpr int ALL = 2; // 最終スコアインデックス
	};


	int m_nGameScore;	// ゲームスコアを格納
	int m_nBonusScore;	// ボーナススコアを格納
	int m_nLastScore;	// 最終スコアを格納

	CResultScore* m_pResultScore[SCORELISTNUM];	// スコアポインタ
};