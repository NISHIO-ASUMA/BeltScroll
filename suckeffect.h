//====================================
//
// 吸い込みエフェクト処理 [ suckeffect.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _SUCKEFFECT_H_ // このマクロ定義がされてなかったら
#define _SUCKEFFECT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "billboard.h"

//*************************************************
// エフェクトクラスを定義
//*************************************************
class CSuckEffect : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CSuckEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CSuckEffect();

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
	static CSuckEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	D3DXVECTOR3 m_targetPos;			// 目標の位置
	int m_nLife;						// 体力
	float m_fRadius;					// 半径
	D3DXVECTOR3 m_move;					// 移動量
};

#endif
