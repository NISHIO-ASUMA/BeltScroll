//=============================================
//
// 敗北プレイヤー処理 [ loseplayer.h ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// インクルードガード
//**************************
#pragma once

//**************************
// インクルードファイル宣言
//**************************
#include "object.h"

//*******************************
// 負けキャラクタークラスを定義
//*******************************
class CLosePlayer : public CObject
{
public:
	//**************************
	// モーションの種類
	//**************************
	enum LOSEMOTION
	{
		LOSEMOTION_NEUTRAL, // 初期値
		LOSEMOTION_ACTION,	// アクション
		LOSEMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CLosePlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CLosePlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 生成関数
	static CLosePlayer* Create(D3DXVECTOR3 pos);

private:

};

