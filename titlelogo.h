//=====================================
//
// タイトルロゴ処理 [ titlelogo.h ]
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
// タイトルロゴクラスを定義
//****************************
class CTitleLogo : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CTitleLogo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleLogo();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTitleLogo* Create(D3DXVECTOR3 pos);

private:

};

