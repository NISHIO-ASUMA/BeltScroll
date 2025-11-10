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
#include "texture.h"
#include "manager.h"

//==============================
// コンストラクタ
//==============================
CBlowerUi::CBlowerUi(int nPriority) : CObject2D(nPriority) , m_nIdxTexture(-1)
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
CBlowerUi* CBlowerUi::Create(D3DXVECTOR3 pos, int nType)
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
	pBlowUi->SetTexture(nType);
	pBlowUi->SetSize(200.0f, 60.0f);
	pBlowUi->SetAnchor(ANCHORTYPE_CENTER);

	// 生成したポインタ
	return pBlowUi;
}
//==============================
// 初期化処理
//==============================
HRESULT CBlowerUi::Init(void)
{
	// オブジェクトの種類を設定
	SetObjType(TYPE_BLOWERUI);

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
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 親クラス処理
	CObject2D::Draw();
}
//================================
// テクスチャ割り当て
//================================
void CBlowerUi::SetTexture(int nType)
{
	// テクスチャポインタをマネージャーから取得
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// 種類によってテクスチャ割り当てを切り替える
	switch (nType)
	{
	case TYPE_SMALL: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_small02.png"); 		// テクスチャ割り当て
		break;

	case TYPE_MIDIUM: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_mid.png"); 		// テクスチャ割り当て
		break;

	case TYPE_FULL: // 
		m_nIdxTexture = pTexture->Register("data/TEXTURE/blower_max02.png"); 	// テクスチャ割り当て
		break;

	default:
		m_nIdxTexture = -1;
		break;
	}
}