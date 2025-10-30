//=============================================
//
// 吸い込みパーティクル処理 [ suckParticle.h ]
// Author: Soichiro Sasaki
//=============================================

#ifndef _SUCKPARTICLE_H_ // このマクロ定義がされてなかったら
#define _SUCKPARTICLE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include <vector>

//*********************
// 前方宣言
//*********************
class CSuckEffect;

//**************************
// パーティクルクラスを定義
//**************************
class CSuckParticle : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CSuckParticle(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CSuckParticle();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CSuckParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos,D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife);

private:
	std::vector<CSuckEffect*> m_pEffect; // エフェクト配列

	D3DXVECTOR3 m_pos;	// 座標
	D3DXVECTOR3 m_targetPos;	// 目標の座標
	D3DXCOLOR m_col;	// 色
	int m_nMaxParticle; // 最大数
	int m_nLife;		// 寿命
	int m_nLength;		// 飛散する距離
	int m_nRadius;		// 粒の大きさ

};

#endif