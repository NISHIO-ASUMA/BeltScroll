//=====================================
//
// 試しのごみ処理 [ trushSim.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _TRUSHSIM_H_ // このマクロ定義がされてなかったら
#define _TRUSHSIM_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CObject;
class CSphereCollider;

//**********************
// 動く床クラスを定義
//**********************
class CTrushSim : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CTrushSim(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CTrushSim();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Controll(void);
	bool Collision(CSphereCollider* pCollider);

	// 静的メンバ関数
	static CTrushSim* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName);

private:
	D3DXVECTOR3 m_posOld;
	CSphereCollider* m_pCollider;				// コライダー
	static constexpr float BLOCKHALF = 0.5f;	// ハーフサイズの固定値
	static constexpr float SPEED = 3.0f;		// 進む速度の固定値
};

#endif