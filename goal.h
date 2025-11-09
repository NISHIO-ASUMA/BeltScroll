//===================================
//
// ゴール地点処理 [ goal.h ]
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
#include "objectX.h"

//***********************************
// ゴールポイントクラスを定義
//***********************************
class CGoal : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CGoal(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGoal();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetIsGoal(bool isFlags) { m_isGoal = isFlags; }
	bool CheckPos(D3DXVECTOR3 pos);
	bool GetIsGoal(void) { return m_isGoal; }

	// 静的メンバ関数
	static CGoal* Create(D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_DestPos; // 目的地座標
	bool m_isGoal;
};