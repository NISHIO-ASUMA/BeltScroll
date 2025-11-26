//===================================
//
// ゴールライン処理 [ goalline.h ]
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

//******************************
// ゴールラインのクラス定義
//******************************
class CGoalLine : public CObjectX
{
public:

	CGoalLine(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGoalLine();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CheckIsGoalPos(const D3DXVECTOR3 pos);

	static CGoalLine* Create(const D3DXVECTOR3 pos,const float fWidth);

	bool isGetGoalPos(void) { return m_isSet; }

private:

	D3DXVECTOR3 m_CheckPos; // 判別座標
	bool m_isSet;			// 到達したか
};