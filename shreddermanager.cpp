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
#include "bonusscore.h"

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
	m_trushBoxCnt = 0;
	m_nStateCnt = 0;
	m_state = STATE_MOVE;
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
	// 交換の処理
	Swap();
	// 状態による処理
	State();
	// ごみステーション用の処理
	TrushBox();
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


//===============================
// 状態ごとの更新
//===============================
void CShredderManager::State(void)
{

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (GetState())
	{
	case STATE_MOVE:
		// 座標移動
		move.x = 0.3f;
		break;
	case STATE_DUSTBOX:
		// 座標移動
		move.x = 0.0f;
		m_nStateCnt++;
		if (m_nStateCnt >= 180)
		{
			m_state = STATE_MOVE;
			m_nStateCnt = 0;
			m_pShredder[0]->GetShredbinManager()->SetNum(0);
			m_pShredder[1]->GetShredbinManager()->SetNum(0);
		}
		break;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pShredder[nCnt]->SetMove(move);
	}
}

//===============================
// ごみステーション用の処理
//===============================
void CShredderManager::TrushBox(void)
{
	 float DUSTBOX_POSX[3] = { DUSTBOX_X00,DUSTBOX_X01,DUSTBOX_X02 };

	if (m_pShredder[0] == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = m_pShredder[0]->GetPos();

	float X = pos.x;

	if (DUSTBOX_POSX[m_trushBoxCnt] <= X)
	{
		CBonusScore::AddTrushBox(m_pShredder[0]->GetShredbinManager()->GetNumAll()+ m_pShredder[1]->GetShredbinManager()->GetNumAll());
		m_state = STATE_DUSTBOX;
		m_trushBoxCnt++;
	}
}


//===============================
// ごみステーションの配置
//===============================
D3DXVECTOR3 CShredderManager::GetTrushBoxPos(void)
{
	float DUSTBOX_POSX[3] = { DUSTBOX_X00,DUSTBOX_X01,DUSTBOX_X02 }; 
	int nCnt = m_trushBoxCnt-1;
	if (nCnt >= 2)
	{// 2以上行かせない
		nCnt = 2;
	}
	return D3DXVECTOR3(DUSTBOX_POSX[nCnt]+200.0f, 50.0f, -600.0f);
}