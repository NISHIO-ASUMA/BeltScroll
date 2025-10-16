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
#include "meshfield.h"
#include "titlelogo.h"
#include "ui.h"

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
	// メッシュフィールド
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// ロゴ生成 ( のちにテクスチャ変更 )
	CTitleLogo::Create(D3DXVECTOR3(1200.0f, 70.0f, 0.0f));

	// UI生成
	CUi::Create(CENTERPOS, 0, 300.0f, 80.0f, "GameName.png", false);
	CUi::Create(D3DXVECTOR3(640.0f,560.0f,0.0f), 0, 220.0f, 60.0f, "Enterkey.png", false);

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{
	// 無し
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