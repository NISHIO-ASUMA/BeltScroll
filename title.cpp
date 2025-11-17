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
	// カメラ初期化
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera) pCamera->Init();

	// メッシュフィールド
	CMeshField::Create(VECTOR3_NULL, 4000.0f, 2000.0f, 1, 1);

	// ロゴ生成
	CTitleLogo::Create(D3DXVECTOR3(1200.0f, 70.0f, 0.0f));

	// UI生成
	CUi::Create(CENTERPOS, 0, 300.0f, 80.0f, "titlename.png", false);
	CUi::Create(D3DXVECTOR3(640.0f,560.0f,0.0f), 0, 220.0f, 60.0f, "titeenter.png", false);

	// タイトルBGM再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_TITLE_BGM);

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
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// ゲーム画面に遷移
		CManager::GetFade()->SetFade(std::make_unique<CGame>());

		// SE再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_CLICKSE);

		return;
	}

	// コントローラー取得
	if (CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_BACK))
	{
		// ゲーム終了
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