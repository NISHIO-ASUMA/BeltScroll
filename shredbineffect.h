//====================================
//
// シュレッドビンエフェクト処理 [ shredbineffect.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _SHREDBINEFFECT_H_ // このマクロ定義がされてなかったら
#define _SHREDBINEFFECT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "billboard.h"

//*************************************************
// エフェクトクラスを定義
//*************************************************
class CShredbinEffect : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CShredbinEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CShredbinEffect();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(void);
	void GetManagerPosition(void);
	void BinUpdate(void);
	void BoxUpdate(void);

	// ゲッター
	static int GetNum(int nType) { return m_nNum[nType]; }

	// 静的メンバ関数
	static CShredbinEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size, D3DXCOLOR col,float fRadius,int m_nType);

private:
	static int m_nNum[2];
	D3DXVECTOR3 m_oldPos;
	D3DXVECTOR3 m_offsetPos;
	D3DXVECTOR3 m_size;
	int m_nIdx;							// 体力
	float m_fRadius;					// 半径
	int m_nType;						// 種類
	D3DXVECTOR3 m_move;					// 移動量
	D3DXVECTOR3 m_shredMove;			// シュレッダーの移動速度
	bool m_bBox;						// ボックス状態初期化用のフラグ
};

#endif
