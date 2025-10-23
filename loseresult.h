//==========================================
//
// 負けリザルトシーン処理 [ loseresult.h ]
// Author: Asuma Nishio
//
//==========================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "scene.h"

//***************************
// 負けリザルトシーンクラス
//***************************
class CLoseResult : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CLoseResult();
	~CLoseResult();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

