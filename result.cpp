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
// 生成処理
//=================================
CResult* CResult::Create(void)
{
	// インスタンス生成
	CResult* pResult = new CResult;

	// 生成に失敗したら
	if (pResult == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pResult->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pResult;
}
//=================================
// 初期化処理
//=================================
HRESULT CResult::Init(void)
{
	// ui生成
	CUi::Create(CENTERPOS,0,60.0f,60.0f,"Enterkey.png",false);

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
		CManager::GetFade()->SetFade(new CRanking());

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
