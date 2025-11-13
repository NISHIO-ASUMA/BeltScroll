//======================================================
//
// シュレッダー管理処理 [ shreddermanager.cpp ]
// Author: Soichiro Sasaki
//
//======================================================

//******************************
// インクルードファイル
//******************************
#include "shreddermanager.h"
#include "shredder.h"
#include "shredbinmanager.h"

const D3DXVECTOR3 CShredderManager::DUSTBOX_POS00 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXVECTOR3 CShredderManager::DUSTBOX_POS01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXVECTOR3 CShredderManager::DUSTBOX_POS02 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//===============================
// コンストラクタ
//===============================
CShredderManager::CShredderManager()
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pShredder[nCnt] = nullptr;
	}
	m_nSwapCnt = 0;
	m_bRedFlont = true;
}
//===============================
// デストラクタ
//===============================
CShredderManager::~CShredderManager()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CShredderManager::Init(void)
{

	m_pShredder[TYPE_RED]=CShredder::Create(D3DXVECTOR3(-400.0f, 142.0f, -250.0f), TYPE_RED);
	m_pShredder[TYPE_GREEN]=CShredder::Create(D3DXVECTOR3(-400.0f, 142.0f, 250.0f), TYPE_GREEN);

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredderManager::Uninit(void)
{
}
//===============================
// 更新処理
//===============================
void CShredderManager::Update(void)
{
	Swap();
}

//===============================
// 交換処理
//===============================
void CShredderManager::Swap(void)
{
	// 交換するタイミング
	if (m_nSwapCnt > SWAPCOUNT)
	{
		m_bRedFlont = !m_bRedFlont;
		m_nSwapCnt = 0;
	}

	// 位置を交換する処理
	if (m_bRedFlont)
	{
		m_pShredder[0]->SetPosZ(FIXED_Z00);
		m_pShredder[1]->SetPosZ(FIXED_Z01);
	}
	else
	{
		m_pShredder[0]->SetPosZ(FIXED_Z01);
		m_pShredder[1]->SetPosZ(FIXED_Z00);
	}

	m_nSwapCnt++;
}
