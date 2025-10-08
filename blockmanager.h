//=====================================
//
// ブロック管理処理 [ blockmanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BLOCKMANAGER_H_ // このマクロ定義がされてなかったら
#define _BLOCKMANAGER_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル
//***************************
#include <vector>
#include "block.h"

//***************************
// 管理クラスを定義
//***************************
class CBlockManager
{
public:
	// コンストラクタ・デストラクタ
	CBlockManager();
	~CBlockManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CBlock* CreateManagerBlock(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scale,const char * pModelName);

private:
	void LoadJsonScript(const char* jsonName); 	// 読み込み

	static std::vector<CBlock*>m_block;	// 動的配列
};

#endif