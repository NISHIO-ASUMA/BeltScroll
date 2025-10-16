//==================================================
//
// パーティクルウィンドウ処理 [ particlepiler.h ]
// Author: Asuma Nishio
// 
// TODO : プレイヤーの前方に扇形に出すイメージ
//
//==================================================

//**********************
// インクルードファイル
//**********************
#include "particlepiler.h"
#include "manager.h"
#include "effect.h"

//=====================================
// オーバーロードコンストラクタ
//=====================================
CParticlePiler::CParticlePiler(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
	m_fAngle = NULL;
}
//=====================================
// デストラクタ
//=====================================
CParticlePiler::~CParticlePiler()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CParticlePiler* CParticlePiler::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife,float fAngle)
{
	// パーティクルのポインタを宣言
	CParticlePiler* pParticle = new CParticlePiler;

	// nullだったら
	if (pParticle == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pParticle->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pParticle->m_pos = pos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;
	pParticle->m_fAngle = fAngle;

	// ポインタを返す
	return pParticle;
}
//=====================================
// 初期化処理
//=====================================
HRESULT CParticlePiler::Init(void)
{
	// 配列クリア
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CParticlePiler::Uninit(void)
{
	// 配列クリア
	m_pEffect.clear();

	// 親クラスの破棄
	CObject::Release();
}
//=====================================
// 更新処理
//=====================================
void CParticlePiler::Update(void)
{
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;

	// 角度
	float fHalfSpread = D3DXToRadian(60.0f);// 扇形の広がり

	for (int nCnt = 0; nCnt < m_nMaxParticle; nCnt++)
	{
		// プレイヤー正面を中心に ±30°の範囲で角度を決定
		float fAngle = m_fAngle + ((float)rand() / RAND_MAX * 2.0f - 1.0f) * fHalfSpread;

		// 
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		float fRise = (float)(rand() % m_nLength) / 50.0f + 0.1f;

		// 移動方向
		D3DXVECTOR3 Move;
		Move.x = -sinf(fAngle) * fRadius;  // 
		Move.z = -cosf(fAngle) * fRadius;  //
		Move.y = fRise;

		// 寿命
		int nLife = ((rand() % m_nLife) + 10);

		// パーティクル生成
		CEffect* pEffect = CEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
			m_pEffect.push_back(pEffect);
		else
			break;
	}

	// 破棄
	Uninit();
}
//=====================================
// 描画処理
//=====================================
void CParticlePiler::Draw(void)
{
	// 無し
}
