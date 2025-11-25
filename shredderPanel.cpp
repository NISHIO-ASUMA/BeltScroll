//=====================================
//
// 動く床処理 [ gimmickfloor.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "shredderPanel.h"
#include "gamemanager.h"
#include "game.h"
#include "object3D.h"

//================================
// オーバーロードコンストラクタ
//================================
CShredderPanel::CShredderPanel(int nPriority) : CObjectX(nPriority)
{
	m_pPanel = nullptr;
	m_nFlachCnt = 0;
	m_nType = 0;
	m_nState = 0;
}
//================================
// デストラクタ
//================================
CShredderPanel::~CShredderPanel()
{
	// 無し
}
//================================
// 生成処理
//================================
CShredderPanel* CShredderPanel::Create(D3DXVECTOR3 pos,int nType)
{
	// インスタンス生成
	CShredderPanel* pPanel = new CShredderPanel;
	if (pPanel == nullptr) return nullptr;

	// オブジェクト設定
	pPanel->SetFilePass("data/MODEL/STAGEOBJ/shredderPanel.x");
	pPanel->m_pPanel = CObject3D::Create(D3DXVECTOR3(pos.x - object3D_offset, pos.y, pos.z), nullptr);
	pPanel->m_nType = nType;
	pPanel->SetPos(pos);

	// 初期化失敗時
	if (FAILED(pPanel->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタ
	return pPanel;
}
//================================
// 初期化処理
//================================
HRESULT CShredderPanel::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();
	m_pPanel->SetSize(30.0f, 30.0f);
	m_pPanel->SetRot(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI*0.5f));
	switch (m_nType)
	{
	case 0:
		m_pPanel->SetCol(COLOR_RED);
		break;
	case 1:
		m_pPanel->SetCol(COLOR_BLUE);
		break;
	}
	return S_OK;
}
//================================
// 終了処理
//================================
void CShredderPanel::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CShredderPanel::Update(void)
{
	// 親クラスの更新
	CObjectX::Update();

	switch (m_nState)
	{
	case STATE_NORMAL:
		// 通常状態
		switch (m_nType)
		{
		case 0:
			m_pPanel->SetCol(COLOR_RED);
			break;
		case 1:
			m_pPanel->SetCol(COLOR_BLUE);
			break;
		}
		break;
	case STATE_FLASH:
		// 点滅
		Flash();
		break;
	}
}

//================================
// 描画処理
//================================
void CShredderPanel::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}

//================================
// 点滅の処理
//================================
void CShredderPanel::Flash(void)
{
	if (m_nFlachCnt < 30)
	{
		switch (m_nType)
		{
		case 0:
			m_pPanel->SetCol(COLOR_RED);
			break;
		case 1:
			m_pPanel->SetCol(COLOR_BLUE);
			break;
		}

	}
	else if(m_nFlachCnt<40)
	{
		m_pPanel->SetCol(COLOR_BLACK);
	}
	else
	{
		m_nFlachCnt = 0;
	}
	m_nFlachCnt++;
}

//================================
// 位置の設定
//================================
void CShredderPanel::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
	pos.x -= object3D_offset;
	m_pPanel->SetPos(pos);
}

//================================
// 位置情報の取得
//================================
D3DXVECTOR3 CShredderPanel::GetPos(void)
{
	return CObjectX::GetPos();
}

