//=====================================
//
// 動く床処理 [ gimmickfloor.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _GIMMICKFLOOR_H_ // このマクロ定義がされてなかったら
#define _GIMMICKFLOOR_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CObject;

//**********************
// 動く床クラスを定義
//**********************
class CGimmickFloor : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CGimmickFloor(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CGimmickFloor();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(void);
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding);

	// 静的メンバ関数
	static CGimmickFloor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName);

private:
	float m_fMoveCnt;		// ブロックを動かすカウント
	static constexpr float COUNTSPEED = 0.01f;	// 1フレームのカウント量
	static constexpr float BLOCKHALF = 0.5f;	// ハーフサイズの固定値
};

#endif