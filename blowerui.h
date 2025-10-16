//====================================
//
// ブロワーUI処理 [ blowerui.h ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードガード
//****************************
#pragma once

//****************************
// インクルードファイル宣言
//****************************
#include "object2D.h"

//****************************
// インクルードファイル宣言
//****************************
class CBlowerUi : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CBlowerUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBlowerUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBlowerUi* Create(D3DXVECTOR3 pos, const char* pFileName);

private:

};

