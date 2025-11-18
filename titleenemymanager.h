//=============================================
//
// タイトルの敵処理 [ titleenemymanager.h ]
// Author: Asuma Nishio
//
//=============================================

//****************************
// インクルードガード
//****************************
#pragma once

//****************************
// インクルードファイル
//****************************
#include <vector>

//****************************
// 前方宣言
//****************************
class CEnemy;

//*******************************
// タイトルの敵管理クラスを定義
//*******************************
class CTitleEnemyManager
{
public:

	CTitleEnemyManager() : m_pEnemy{} {};
	~CTitleEnemyManager() = default;

	HRESULT Init(void);
	void Uninit(void);
	void Load(void);
	void PushBack(CEnemy* pEnemy) { m_pEnemy.push_back(pEnemy); }

	CEnemy* CreateManagerT(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pModelName, int nMass, int nColor);

private:

	std::vector<CEnemy*>m_pEnemy; // 動的配列
};