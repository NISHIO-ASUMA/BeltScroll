//========================================
//
// ゴール管理処理 [ goalmanager.h ]
// Author: Asuma Nishio
//
//========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// 前方宣言
//**********************
class CGoal;

//**********************
// 管理クラスを定義
//**********************
class CGoalManager
{
public:

	CGoalManager();
	~CGoalManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 取得
	CGoal* GetGoal(const int nIdx) { return m_pGoal[nIdx]; }

private:

	static constexpr int NUM_GOAL = 2;

	CGoal* m_pGoal[NUM_GOAL]; // ゴールモデル数

};