//=============================================
//
// 風パーティクル処理 [ windparticle.cpp ]
// Author: Asuma Nishio
//
//=============================================

//*************************
// インクルードファイル
//*************************
#include "windparticle.h"
#include "effect.h"

//===========================
// コンストラクタ
//===========================
CWindParticle::CWindParticle(int nPriority) : CObject(nPriority),
m_pos(VECTOR3_NULL),
m_pEffect{},
m_nLength(NULL),
m_nLife(NULL),
m_nMax(NULL),
m_nRadius(NULL),
m_col(COLOR_WHITE)
{

}
//===========================
// デストラクタ
//===========================
CWindParticle::~CWindParticle()
{

}
//===========================
// 生成処理
//===========================
CWindParticle* CWindParticle::Create(const D3DXVECTOR3 pos, const int nMax, const int nLife, const int nLength, const int nRadius,const D3DXCOLOR col)
{
	// インスタンス生成
	CWindParticle* pWind = new CWindParticle;
	if (pWind == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pWind->Init())) return nullptr;

	// オブジェクト設定
	pWind->m_pos = pos;
	pWind->m_nMax = nMax;
	pWind->m_nLife = nLife;
	pWind->m_nLength = nLength;
	pWind->m_nRadius = nRadius;
	pWind->m_col = col;

	return pWind;
}
//===========================
// 初期化処理
//===========================
HRESULT CWindParticle::Init(void)
{
	// 値のクリア
	m_pEffect.clear();

	return S_OK;
}
//===========================
// 終了処理
//===========================
void CWindParticle::Uninit(void)
{
	CObject::Release();
}
//===========================
// 更新処理
//===========================
void CWindParticle::Update(void)
{
	//カラーの設定
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;

	// パーティクルの生成
	for (int nCntApper = 0; nCntApper < m_nMax; nCntApper++)
	{
		// 
		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 
		dir.x += ((float)(rand() % 125 - 50)) * 0.025f;
		dir.y += ((float)(rand() % 125 - 50)) * 0.025f;

		// 正規化
		D3DXVec3Normalize(&dir, &dir);

		// 長さ
		float fLength = ((float)(rand() % m_nLength) / 10.0f) + 0.5f;

		// 移動ベクトル
		D3DXVECTOR3 Move = dir * fLength;

		// 半径の設定
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.66f);

		// 寿命の設定
		int nLife = (static_cast<float>(rand() % m_nLife) / 10);

		// エフェクト生成
		CEffect* pEffect = CEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
		{
			m_pEffect.push_back(pEffect);
		}
		else
		{
			break;
		}
	}
	// 破棄
	Uninit();
}
//===========================
// 描画処理
//===========================
void CWindParticle::Draw(void)
{

}