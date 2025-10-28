//===========================================
//
// 紙吹雪エフェクト処理 [ confettieffect.cpp ]
// Author: Soichiro Sasaki
//
//===========================================

//**********************
// インクルードファイル
//**********************
#include "confettieffect.h"
#include "manager.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CConfettiEffect::CConfettiEffect(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//===============================
// デストラクタ
//===============================
CConfettiEffect::~CConfettiEffect()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CConfettiEffect* CConfettiEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// エフェクトポインタ
	CConfettiEffect* pEffect = new CConfettiEffect;

	// nullptrだったら
	if (pEffect == nullptr) return nullptr;

	// 初期化に失敗したら
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// 3Dオブジェクトセット
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);
	pEffect->SetTexture("confetti.jpg");

	// 半径を代入
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->SetLife(nLife);

	// エフェクトポインタを返す
	return pEffect;
}
//===============================
// 初期化処理
//===============================
HRESULT CConfettiEffect::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CConfettiEffect::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//===============================
// 更新処理
//===============================
void CConfettiEffect::Update(void)
{
	// 座標,カラー取得
	D3DXVECTOR3 Effectpos = GetPos();
	D3DXVECTOR3 Effectrot = GetRot();

	//カラーの設定
	D3DXCOLOR col = GetCol();

	// オブジェクト更新
	CBillboard::Update();

	// 移動量の更新
	Effectpos += m_move;
	m_move.y -= 0.4f;

	// 減算する値を設定
	const float fDecPow = 0.005f;

	// 半径をデクリメント
	m_fRadius -= fDecPow;

	// α値を減少
	col.a -= fDecPow;

	Effectrot.z += 0.2f;

	// 座標をセットする
	SetPos(Effectpos);

	// 向きをセットする
	SetRot(Effectrot);

	// カラーをセット
	SetCol(col);

	// 0以下なら
	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// サイズセット
	SetSize(m_fRadius, m_fRadius);

	// 体力を減らす
	m_nLife--;

	// 0以下の時
	if (m_nLife <= NULL)
	{
		// 削除する
		Uninit();
	}
}
//===============================
// 描画処理
//===============================
void CConfettiEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// αブレンディングの加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ビルボード描画
	CBillboard::Draw();

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// αブレンディングを戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}