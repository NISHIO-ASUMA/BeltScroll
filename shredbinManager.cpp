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

int CShredbinManager::m_nNum = 0;

//===============================
// コンストラクタ
//===============================
CShredbinManager::CShredbinManager()
{
	m_pos = VECTOR3_NULL;
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

	if (pKey->GetPress(DIK_9))
	{
		m_nNum++;
	}
	else if(pKey->GetPress(DIK_8)&&m_nNum>0)
	{
		m_nNum--;
	}

	if (m_nNum > CShredbinEffect::GetNumAll())
	{
		CShredbinEffect::Create(m_pos, D3DXVECTOR3(200.0f, 200.0f, 200.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5,0);
	}
}