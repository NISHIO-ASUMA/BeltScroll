//=========================================================
//
// リザルト用ゴミ箱処理 [ resulttrush.h ]
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
#include "objectX.h"

//*********************************************************
// ゴミ箱クラスを定義
//*********************************************************
class CResultTrush : public CObjectX
{
public:

	CResultTrush(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CResultTrush() = default;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCol(D3DXCOLOR col) { m_col = col; }

	static CResultTrush* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,const D3DXCOLOR col);

private:
	
	int m_nParticleTimer;			// エフェクト生成タイマー
	int m_nParticleInterval;		// 生成間隔
	int m_nMaxTime;					// 最大時間
	D3DXCOLOR m_col;
};