//=====================================
//
// タイトルロゴ処理 [ titlelogo.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "titlelogo.h"

//****************************
// 定数空間宣言
//****************************
namespace LOGOINFO
{
	constexpr float WIDTH = 60.0f; // 横幅
	constexpr float HEIGHT = 60.0f; // 高さ
}

//================================
// オーバーロードコンストラクタ
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
}
//================================
// デストラクタ
//================================
CTitleLogo::~CTitleLogo()
{
	// 無し
}
//================================
// 生成処理
//================================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTitleLogo* pLogo = new CTitleLogo;
	if (pLogo == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pLogo->Init()))
	{
		return nullptr;
	}

	// 2Dオブジェクト設定
	pLogo->SetPos(pos);
	pLogo->SetHeight(LOGOINFO::HEIGHT);
	pLogo->SetWidth(LOGOINFO::WIDTH);
	pLogo->SetAnchor(ANCHORTYPE_CENTER);
	pLogo->SetTexture("TitleLogo.png");

	// 生成されたポインタ
	return pLogo;
}
//================================
// 初期化処理
//================================
HRESULT CTitleLogo::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// 初期化結果
	return S_OK;
}
//================================
// 終了処理
//================================
void CTitleLogo::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//================================
// 更新処理
//================================
void CTitleLogo::Update(void)
{
	// 親クラスの更新処理
	CObject2D::Update();
}
//================================
// 描画処理
//================================
void CTitleLogo::Draw(void)
{
	// 親クラスの描画処理
	CObject2D::Draw();
}