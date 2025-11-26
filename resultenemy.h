//================================================
//
// リザルトの敵管理処理 [ resultenemy.h ]
// Author: Asuma Nishio
//
//================================================

//***********************************
// インクルードガード
//***********************************
#pragma once

//***********************************
// インクルードファイル
//***********************************
#include <vector>
#include <string>

//***********************************
// 前方宣言
//***********************************
class CEnemy;

//***********************************
// リザルトに配置する敵のクラス定義
//***********************************
class CResultEnemy
{
public:

	CResultEnemy() : m_pEnemy{} {};
	~CResultEnemy() = default;

	HRESULT Init(const char * pFileName);
	void Uninit(void);
	void Load(const char * pFileName);
	void PushBack(CEnemy * pEnemy) { m_pEnemy.push_back(pEnemy); }

	CEnemy* CreateManagerT(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pModelName, int nMass, int nColor);

private:

	std::vector<CEnemy*>m_pEnemy; // 動的配列
};