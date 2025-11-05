//=============================================
//
// 風パーティクル処理 [ windparticle.h ]
// Author: Asuma Nishio
//
//=============================================

//*************************
// インクルードガード
//*************************
#pragma once

//*************************
// インクルードファイル
//*************************
#include "object.h"
#include <vector>

//*************************
// 前方宣言
//*************************
class CEffect;

//*****************************
// 風パーティクルクラスを定義
//*****************************
class CWindParticle : public CObject
{
public:

	// コンストラクタ・デストラクタ
	CWindParticle(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CWindParticle();

	// 初期化処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CWindParticle* Create(const D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_pos; // 座標
	std::vector<CEffect*>m_pEffect; // エフェクト配列
};

