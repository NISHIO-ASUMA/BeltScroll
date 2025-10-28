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
// UIクラスを宣言
//****************************
class CBlowerUi : public CObject2D
{
public:
	//***************************
	// 種類を定義
	//***************************
	enum TYPE
	{
		TYPE_SMALL,
		TYPE_MIDIUM,
		TYPE_FULL,
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CBlowerUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBlowerUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(int nType);

	// 静的メンバ関数
	static CBlowerUi* Create(D3DXVECTOR3 pos, int nType);

private:
	int m_nIdxTexture;
};

