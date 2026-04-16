//=========================================================
//
// ステンシルシャドウ処理 [ shadowS.h ]
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
// シャドウステンシルクラスを定義
//*********************************************************
class CShadowS :public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CShadowS(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadowS();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;		// 頂点バッファ
	bool m_isDraw;						// 描画フラグ
};
