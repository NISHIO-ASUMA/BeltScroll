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
	// リザルトプレイヤー生成
	CLosePlayer::Create(D3DXVECTOR3(0.0f,0.0f,-200.0f));

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