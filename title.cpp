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
#include "meshfield.h"

//=====================================
// コンストラクタ
//=====================================
CTitle::CTitle() : CScene(CScene::MODE_TITLE)
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

	// CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

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
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ランキング
		CManager::GetFade()->SetFade(new CGame());

		return;
	}

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
CTitle* CTitle::Create()
{
	// インスタンス生成
	CTitle* pTitle = new CTitle();

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