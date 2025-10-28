//=============================================
//
// 紙吹雪パーティクル処理 [ confettiparticle.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _CONFETTIPARTICLE_H_ // このマクロ定義がされてなかったら
#define _CONFETTIPARTICLE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include <vector>

//*********************
// 前方宣言
//*********************
class CConfettiEffect;

//**************************
// パーティクルクラスを定義
//**************************
class CConfettiParticle : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CConfettiParticle(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CConfettiParticle();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CConfettiParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife, float fAngle);

private:
	std::vector<CConfettiEffect*> m_pEffect; // エフェクト配列

	D3DXVECTOR3 m_pos;	// 座標
	D3DXCOLOR m_col;	// 色
	int m_nMaxParticle; // 最大数
	int m_nLife;		// 寿命
	int m_nLength;		// 飛散する距離
	int m_nRadius;		// 粒の大きさ
	float m_fAngle;		// 角度

};

#endif