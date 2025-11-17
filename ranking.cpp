//=======================================
//
// ランキングシーン処理 [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// インクルードファイル宣言
//******************************
#include "ranking.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "ui.h"
#include "rankingscore.h"

//===================================
// オーバーロードコンストラクタ
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	// 値のクリア
}
//===================================
// デストラクタ
//===================================
CRanking::~CRanking()
{
	// 無し
}
//===================================
// 初期化処理
//===================================
HRESULT CRanking::Init(void)
{
	// ui生成
	CUi::Create(CENTERPOS, 0, 640.0f, 360.0f, "ranking.jpg", false);

	// ランキングスコア生成
	CRankingScore::Create(D3DXVECTOR3(850.0f, 180.0f, 0.0f), 250.0f, 40.0f);

	// ランキングBGM再生
	// CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RANKINGBGM);

	// 初期化結果を返す
	return S_OK;
}
//===================================
// 終了処理
//===================================
void CRanking::Uninit(void)
{

}
//===================================
// 更新処理
//===================================
void CRanking::Update(void)
{
	// 決定キー入力
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// タイトル遷移
		pFade->SetFade(std::make_unique<CTitle>());

		return;
	}
}
//===================================
// 描画処理
//===================================
void CRanking::Draw(void)
{
	// 無し
}