//======================================================
//
// シュレッダー管理処理 [ shreddermanager.cpp ]
// Author: Soichiro Sasaki
//
//======================================================

//******************************
// インクルードファイル
//******************************
#include "shredbinmanager.h"
#include "shredbineffect.h"
#include "input.h"
#include "manager.h"
#include "shreddermanager.h"

//===============================
// コンストラクタ
//===============================
CShredbinManager::CShredbinManager()
{
	m_pos = VECTOR3_NULL;
	m_move = VECTOR3_NULL;
	m_nType = 0;
	for (int nCnt = 0; nCnt < CShredderManager::TYPE_MAX; nCnt++)
	{
		m_nNum[nCnt] = 0;
	}
}

//===============================
// デストラクタ
//===============================
CShredbinManager::~CShredbinManager()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CShredbinManager::Init(void)
{

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredbinManager::Uninit(void)
{

}
//===============================
// 更新処理
//===============================
void CShredbinManager::Update(void)
{
	CInputKeyboard* pKey = CManager::GetInputKeyboard();

	if (m_nNum[m_nType] > CShredbinEffect::GetNum(m_nType))
	{
		D3DXCOLOR col = COLOR_NULL;
		if (m_nType==0)
		{// 赤色
			col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		}
		else
		{// 青色
			col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		}

		CShredbinEffect::Create(m_pos,m_move, D3DXVECTOR3(100.0f, 80.0f, 500.0f), col, 6,m_nType);
	}
}