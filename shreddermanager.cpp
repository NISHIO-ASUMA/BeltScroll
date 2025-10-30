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
	m_pA = nullptr;
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
	m_pA = new CShredbinManager;
	m_pA->Init();
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredderManager::Uninit(void)
{
	m_pA->Uninit();
	delete m_pA;
	m_pA = nullptr;
}
//===============================
// 更新処理
//===============================
void CShredderManager::Update(void)
{
	Swap();
	m_pA->Update();
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
