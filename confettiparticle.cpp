//==================================================
//
// 紙吹雪パーティクル処理 [ confettiparticle.h ]
// Author: Soichiro Sasaki
//
//==================================================

//**********************
// インクルードファイル
//**********************
#include "confettiparticle.h"
#include "manager.h"
#include "confettieffect.h"

//=====================================
// オーバーロードコンストラクタ
//=====================================
CConfettiParticle::CConfettiParticle(int nPriority) : CObject(nPriority)
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
CConfettiParticle::~CConfettiParticle()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CConfettiParticle* CConfettiParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife, float fAngle)
{
	// パーティクルのポインタを宣言
	CConfettiParticle* pParticle = new CConfettiParticle;

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
HRESULT CConfettiParticle::Init(void)
{
	// 配列クリア
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CConfettiParticle::Uninit(void)
{
	// 配列クリア
	m_pEffect.clear();

	// 親クラスの破棄
	CObject::Release();
}
//=====================================
// 更新処理
//=====================================
void CConfettiParticle::Update(void)
{
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;

	// 角度
	float fHalfSpread = D3DXToRadian(30.0f);// 扇形の広がり

	for (int nCnt = 0; nCnt < m_nMaxParticle; nCnt++)
	{
		// プレイヤー正面を中心に ±30°の範囲で角度を決定
		float fAngle = m_fAngle + ((float)rand() / RAND_MAX * 2.0f - 1.0f) * fHalfSpread;

		// 
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		float fRise = (float)(rand() % m_nLength) / 50.0f + 7.0f;

		// 移動方向
		D3DXVECTOR3 Move;
		Move.x = -sinf(fAngle) * fRadius;  // 
		Move.z = -cosf(fAngle) * fRadius;  //
		Move.y = fRise;

		// 寿命
		int nLife = ((rand() % m_nLife) + 10);

		// パーティクル生成
		CConfettiEffect* pEffect = CConfettiEffect::Create(pos, col, Move, nLife, fRadius);

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
void CConfettiParticle::Draw(void)
{
	// 無し
}
