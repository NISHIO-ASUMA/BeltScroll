//=====================================
//
// ブロック処理 [ block.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BLOCK_H_ // このマクロ定義がされてなかったら
#define _BLOCK_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CObject;
class CAABBCollider;

//**********************
// ブロッククラスを定義
//**********************
class CBlock : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CBlock();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CAABBCollider * pOther,D3DXVECTOR3 * pOutPos);
	CAABBCollider* GetCollider(void) { return m_pAABB;}

	// 静的メンバ関数
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale,const char* FileName);

private:
	static constexpr float BLOCKHALF = 0.5f;	// ハーフサイズの固定値
	CAABBCollider* m_pAABB;		// 矩形コライダー
};

#endif