//================================================
//
// リザルト用ブロック処理 [ resultobject.h ]
// Author: Asuma Nishio
//
//================================================

//******************************
// インクルードガード
//******************************
#pragma once

//******************************
// インクルードファイル
//******************************
#include <vector>

//******************************
// 前方宣言
//******************************
class CBlock;

//*****************************************
// リザルトに出すマップブロッククラス
//*****************************************
class CResultBlock
{
public:

	CResultBlock();
	~CResultBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void PushBack(CBlock* pBlock) { m_resultblock.push_back(pBlock); }

	CBlock* CreateBlock(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale,const char* pModelName);

private:

	void LoadJson(void);

	std::vector<CBlock*>m_resultblock;	// 動的配列
};