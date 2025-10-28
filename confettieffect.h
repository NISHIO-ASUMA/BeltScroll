//====================================
//
// 紙吹雪エフェクト処理 [ confettieffect.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _CONFETTIEFFECT_H_ // このマクロ定義がされてなかったら
#define _CONFETTIEFFECT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "billboard.h"

//*************************************************
// エフェクトクラスを定義
//*************************************************
class CConfettiEffect : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CConfettiEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CConfettiEffect();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetLife(int nLife) { m_nLife = nLife; }

	// ゲッター
	int GetLife(void) { return m_nLife; }

	// 静的メンバ関数
	static CConfettiEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;						  // 体力
	float m_fRadius;					  // 半径
	D3DXVECTOR3 m_move;					  // 移動量
};

#endif
