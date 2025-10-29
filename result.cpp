//====================================
//
// リザルトシーン処理 [ result.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "result.h"
#include "ui.h"
#include "manager.h"
#include "ranking.h"
#include "winplayer.h"
#include "meshfield.h"

//=================================
// オーバーロードコンストラクタ
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT)
{
}
//=================================
// デストラクタ
//=================================
CResult::~CResult()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CResult::Init(void)
{
	// ui生成
	// CUi::Create(CENTERPOS,0,640.0f,360.0f,"GameClear.jpg",false);

	// プレイヤー生成
	CWinPlayer::Create(VECTOR3_NULL);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// サウンド再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResult::Uninit(void)
{

}
//=================================
// 更新処理
//=================================
void CResult::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ランキング
		CManager::GetFade()->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//=================================
// 描画処理
//=================================
void CResult::Draw(void)
{
	// 無し
}