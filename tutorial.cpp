//=====================================
//
// チュートリアル処理 [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "tutorial.h"
#include "manager.h"
#include "sound.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{

}
//===============================
// デストラクタ
//===============================
CTutorial::~CTutorial()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CTutorial::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_TUTORIALBGM);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CTutorial::Uninit(void)
{

}
//===============================
// 更新処理
//===============================
void CTutorial::Update(void)
{

}
//===============================
// 描画処理
//===============================
void CTutorial::Draw(void)
{
	// 無し
}
//===============================
// 生成処理
//===============================
CTutorial* CTutorial::Create(void)
{
	// インスタンス生成
	CTutorial* pTutorial = new CTutorial;

	// 生成失敗時
	if (pTutorial == nullptr) return nullptr;

	// もし初期化に失敗したら
	if (FAILED(pTutorial->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTutorial;
}