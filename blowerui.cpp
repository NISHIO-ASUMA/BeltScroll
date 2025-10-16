//====================================
//
// ブロワーUI処理 [ blowerui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//***************************
// インクルードファイル宣言
//***************************
#include "blowerui.h"

//***************************
// 定数空間
//***************************
namespace BLOWUI
{


};

//==============================
// コンストラクタ
//==============================
CBlowerUi::CBlowerUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
}
//==============================
// デストラクタ
//==============================
CBlowerUi::~CBlowerUi()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CBlowerUi* CBlowerUi::Create(D3DXVECTOR3 pos, const char* pFileName)
{
	// インスタンス生成
	CBlowerUi* pBlowUi = new CBlowerUi;
	if (pBlowUi == nullptr) return nullptr;

	if (FAILED(pBlowUi->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pBlowUi->SetPos(pos);
	pBlowUi->SetTexture(pFileName);
	pBlowUi->SetSize(60.0f, 60.0f);
	pBlowUi->SetAnchor(ANCHORTYPE_CENTER);

	// 生成したポインタ
	return pBlowUi;
}
//==============================
// 初期化処理
//==============================
HRESULT CBlowerUi::Init(void)
{
	// 親クラス処理
	CObject2D::Init();

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CBlowerUi::Uninit(void)
{
	// 親クラス処理
	CObject2D::Uninit();
}
//==============================
// 更新処理
//==============================
void CBlowerUi::Update(void)
{
	// 親クラス処理
	CObject2D::Update();
}
//==============================
// 描画処理
//==============================
void CBlowerUi::Draw(void)
{
	// 親クラス処理
	CObject2D::Draw();
}