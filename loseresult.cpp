//============================================
//
// 負けリザルトシーン処理 [ loseresult.cpp ]
// Author: Asuma Nishio
//
//============================================

//***********************
// インクルードファイル
//***********************
#include "loseresult.h"
#include "ui.h"
#include "manager.h"
#include "fade.h"
#include "ranking.h"
#include "loseplayer.h"
#include "meshfield.h"

//==============================
// コンストラクタ
//==============================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// 値のクリア
}
//==============================
// デストラクタ
//==============================
CLoseResult::~CLoseResult()
{

}
//==============================
// 初期化処理
//==============================
HRESULT CLoseResult::Init(void)
{
	// カメラ初期化
	CManager::GetCamera()->Init();

	// UI生成
	CUi::Create(D3DXVECTOR3(640.0f, 205.0f, 0.0f), 0, 240.0f, 60.0f, "out.png", false);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// 負けリザルトプレイヤー生成
	CLosePlayer::Create(VECTOR3_NULL);	
		
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CLoseResult::Uninit(void)
{

}
//==============================
// 更新処理
//==============================
void CLoseResult::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// 画面遷移
		pFade->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//==============================
// 描画処理
//==============================
void CLoseResult::Draw(void)
{
	// 無し
}