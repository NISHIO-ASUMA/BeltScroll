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
	static CWindParticle* Create(const D3DXVECTOR3 pos,const int nMax,const int nLife,const int nLength,const int nRadius, const D3DXCOLOR col);

private:

	D3DXVECTOR3 m_pos; // 座標
	D3DXCOLOR m_col;

	int m_nMax;
	int m_nLife;
	int m_nLength;		// 飛散する距離
	int m_nRadius;		// 粒の大きさ

	std::vector<CEffect*>m_pEffect; // エフェクト配列
};

