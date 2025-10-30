//====================================
//
// シュレッドビンエフェクト処理 [ shredbinffect.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "shredbineffect.h"
#include "manager.h"
#include "shredbinmanager.h"

int CShredbinEffect::m_nNumAll = 0;

//===============================
// オーバーロードコンストラクタ
//===============================
CShredbinEffect::CShredbinEffect(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_oldPos = VECTOR3_NULL;
	m_size = VECTOR3_NULL;
	m_nIdx = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//===============================
// デストラクタ
//===============================
CShredbinEffect::~CShredbinEffect()
{
	m_nNumAll--;
}

//===============================
// 生成処理
//===============================
CShredbinEffect* CShredbinEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, float fRadius)
{
	// エフェクトポインタ
	CShredbinEffect* pEffect = new CShredbinEffect;

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
	pEffect->SetTexture("effect000.jpg");

	// 半径を代入
	pEffect->m_offsetPos = pos;
	pEffect->m_fRadius = fRadius;
	pEffect->m_size = size;
	pEffect->m_nIdx = m_nNumAll;
	m_nNumAll++;

	// エフェクトポインタを返す
	return pEffect;
}
//===============================
// 初期化処理
//===============================
HRESULT CShredbinEffect::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();
	m_move.x = ((float)(rand() % 3) - 1.0f) * 3.0f;
	m_move.y = ((float)(rand() % 3) - 1.0f) * 3.0f;
	m_move.z = ((float)(rand() % 3) - 1.0f) * 3.0f;

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredbinEffect::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//===============================
// 更新処理
//===============================
void CShredbinEffect::Update(void)
{
	// 座標,カラー取得
	D3DXVECTOR3 Effectpos = GetPos();
	m_oldPos = Effectpos;
	//カラーの設定
	D3DXCOLOR col = GetCol();

	// オブジェクト更新
	CBillboard::Update();

	D3DXVECTOR3 vec;

	// 移動量の更新
	Effectpos += m_move;

	// 減算する値を設定
	const float fDecPow = 0.005f;

	// 座標をセットする
	SetPos(Effectpos);

	Collision();

	// 0以下なら
	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// サイズセット
	SetSize(m_fRadius, m_fRadius);

	// 0以下の時
	if (m_nIdx > CShredbinManager::GetNumAll())
	{
		// 削除する
		Uninit();
	}
}
//===============================
// 描画処理
//===============================
void CShredbinEffect::Draw(void)
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

void CShredbinEffect::Collision(void)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_offsetPos.x + m_size.x * 0.5f <= pos.x && m_offsetPos.x + m_size.x * 0.5f > m_oldPos.x
		|| m_offsetPos.x - m_size.x * 0.5f >= pos.x && m_offsetPos.x - m_size.x * 0.5f < m_oldPos.x
		|| m_offsetPos.y + m_size.y * 0.5f <= pos.y && m_offsetPos.y + m_size.y * 0.5f > m_oldPos.y
		|| m_offsetPos.y - m_size.y * 0.5f >= pos.y && m_offsetPos.y - m_size.y * 0.5f < m_oldPos.y
		|| m_offsetPos.z + m_size.z * 0.5f <= pos.z && m_offsetPos.z + m_size.z * 0.5f > m_oldPos.z
		|| m_offsetPos.z - m_size.z * 0.5f >= pos.z && m_offsetPos.z - m_size.z * 0.5f < m_oldPos.z)
	{
		pos = m_oldPos;
		D3DXVECTOR3 vecPos;

		vecPos.x = ((float)(rand() % 100) - 50.0f);
		vecPos.y = ((float)(rand() % 100) - 50.0f);
		vecPos.z = ((float)(rand() % 100) - 50.0f);

		D3DXVECTOR3 nor = vecPos - VECTOR3_NULL;
		D3DXVec3Normalize(&nor, &nor);
		m_move = nor * 3.0f;
	}

	SetPos(pos);
}