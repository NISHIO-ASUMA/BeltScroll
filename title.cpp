//====================================
//
// タイトル処理 [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"

//=====================================
// コンストラクタ
//=====================================
CTitle::CTitle(bool isFirst) : CScene(CScene::MODE_TITLE), m_isCreate(isFirst)
{
	//無し
}
//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{
	// 無し
}
//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	// ui生成
	// CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, 120.0f, 30.0f, "bullet.png", false);

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{

}
//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{
	// コントローラー取得
	if (CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_BACK))
	{
		PostQuitMessage(0);
		return;
	}
}
//=====================================
// 描画処理
//=====================================
void CTitle::Draw(void)
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create(bool isFirst)
{
	// インスタンス生成
	CTitle* pTitle = new CTitle(isFirst);

	// nullだったら
	if (pTitle == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTitle;
}