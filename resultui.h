//===================================
//
// リザルト演出ui処理 [ resultui.h ]
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
#include "object2D.h"

//******************************
// リザルトに出すUIクラス
//******************************
class CResultUi : public CObject2D
{
public:

	CResultUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName);

private:

	static constexpr float BASE_X = 845.0f;
};