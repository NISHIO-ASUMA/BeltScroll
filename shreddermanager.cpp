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
#include "objectX.h"
#include "manager.h"

//******************************
// 静的メンバ変数宣言
//******************************
const D3DXVECTOR3 CShredderManager::HOSE_ENTRANCE_OFFSET = D3DXVECTOR3(-70.0f,80.0f,0.0f);
const D3DXVECTOR3 CShredderManager::HOSE_EXIT_OFFSET = D3DXVECTOR3(90.0f, -80.0f, -40.0f);
const D3DXVECTOR3 CShredderManager::DUST_OFFSET = D3DXVECTOR3(170.0f, 30.0f, -550.0f);

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
	m_isSaveScoreTrush = false;
	m_isSound = false;
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
	// シュレッダー生成
	m_pShredder[TYPE_RED]=CShredder::Create(D3DXVECTOR3(-400.0f, 110.0f, -250.0f), TYPE_RED);
	m_pShredder[TYPE_BLUE]=CShredder::Create(D3DXVECTOR3(-400.0f, 110.0f, 250.0f), TYPE_BLUE);
	m_pHose = CObjectX::Create("data/MODEL/STAGEOBJ/shredderHose.x",D3DXVECTOR3(-320.0f, 250.0f, -500.0f));

	// ゴミ箱生成
	CObjectX::Create("data/MODEL/STAGEOBJ/TrushBox.x", D3DXVECTOR3(DUSTBOX_X00 + DUST_OFFSET.x, DUST_OFFSET.y, DUST_OFFSET.z));
	CObjectX::Create("data/MODEL/STAGEOBJ/TrushBox.x", D3DXVECTOR3(DUSTBOX_X01 + DUST_OFFSET.x, DUST_OFFSET.y, DUST_OFFSET.z));
	CObjectX::Create("data/MODEL/STAGEOBJ/TrushBox.x", D3DXVECTOR3(DUSTBOX_X02 + DUST_OFFSET.x, DUST_OFFSET.y, DUST_OFFSET.z));
	CObjectX::Create("data/MODEL/STAGEOBJ/TrushBox.x", D3DXVECTOR3(DUSTBOX_X03 + DUST_OFFSET.x, DUST_OFFSET.y, DUST_OFFSET.z));
	CObjectX::Create("data/MODEL/STAGEOBJ/TrushBox.x", D3DXVECTOR3(DUSTBOX_X04 + DUST_OFFSET.x, DUST_OFFSET.y, DUST_OFFSET.z));

	// ボーナススコアをクリアする
	CBonusScore::ClearScore();

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

	// 状態による処理
	State();
	// ごみステーション用の処理
	TrushBox();

	//// 止まっているなら処理をさせない
	//if (m_pShredder[TYPE_RED]->GetStop() || m_pShredder[TYPE_BLUE]->GetStop())
	//{
	//	return;
	//}

	// 交換の処理
	Swap();
}

//===============================
// 交換処理
//===============================
void CShredderManager::Swap(void)
{
	if (m_pShredder[0]->GetStop() || m_pShredder[1]->GetStop())
	{
		m_nSwapCnt = 0;
		return;
	}

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
		UpdateHose();
		break;
	case STATE_DUSTBOX:
		// 座標移動
		move.x = 0.0f;
		m_nStateCnt++;
		if (m_nStateCnt >= 240)
		{
			m_state = STATE_MOVE;
			m_nStateCnt = 0;
			m_pShredder[TYPE_RED]->GetShredbinManager()->SetNum(NULL);
			m_pShredder[TYPE_BLUE]->GetShredbinManager()->SetNum(NULL);

			m_isSound = false;
		}
		break;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pShredder[nCnt]->GetStop())
		{
			move.x = 0.0f;
		}
		m_pShredder[nCnt]->SetMove(move);
	}
}

//===============================
// ごみステーション用の処理
//===============================
void CShredderManager::TrushBox(void)
{
	float DUSTBOX_POSX[5] = { DUSTBOX_X00,DUSTBOX_X01,DUSTBOX_X02 ,DUSTBOX_X03 ,DUSTBOX_X04 };

	if (m_pShredder[0] == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = m_pShredder[0]->GetPos();

	float X = pos.x;

	if (DUSTBOX_POSX[m_trushBoxCnt] <= X)
	{
		if (!m_isSound)
		{
			// サウンド再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BOUNSSE);

			// 一度再生したらそのフレーム間は流さない
			m_isSound = true;
		}
		
		// 加算
		CBonusScore::AddTrushBox(m_pShredder[0]->GetShredbinManager()->GetNumAll()+ m_pShredder[1]->GetShredbinManager()->GetNumAll());

		// 状態変更
		m_state = STATE_DUSTBOX;

		// カウント加算
		m_trushBoxCnt++;
	}

	// 最後のゴミステーションに入ったら
	if (m_trushBoxCnt >= LAST_TRASH_NUMBER && !m_isSaveScoreTrush)
	{
		// フラグを有効化
		m_isSaveScoreTrush = true;

		// ボーナススコアを書き出す
		CBonusScore::Save();
	}
}

void CShredderManager::UpdateHose(void)
{
	D3DXVECTOR3 pos=m_pHose->GetPos();

	pos.x += 0.3f;

	m_pHose->SetPos(pos);
}

//===============================
// ごみステーションの配置
//===============================
D3DXVECTOR3 CShredderManager::GetTrushBoxPos(void)
{
	float DUSTBOX_POSX[5] = { DUSTBOX_X00,DUSTBOX_X01,DUSTBOX_X02 ,DUSTBOX_X03 ,DUSTBOX_X04 };
	int nCnt = m_trushBoxCnt-1;
	if (nCnt >= LAST_TRASH_NUMBER)
	{ 
		
		nCnt = LAST_TRASH_NUMBER;
	}
	return D3DXVECTOR3(DUSTBOX_POSX[nCnt]+200.0f, 50.0f, -600.0f);
}

//===============================
// ホースの位置情報
//===============================
D3DXVECTOR3 CShredderManager::GetHosePos(bool bExit)
{
	D3DXVECTOR3 pos = m_pHose->GetPos();
	if (bExit == true)
	{
		pos += HOSE_EXIT_OFFSET;
	}
	else
	{
		pos += HOSE_ENTRANCE_OFFSET;
	}
	return pos;
}