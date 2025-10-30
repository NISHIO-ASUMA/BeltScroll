//==================================================
//
// 吸い込みパーティクル処理 [ suckParticle.h ]
// Author: Soichiro Sasaki
//
//==================================================

//**********************
// インクルードファイル
//**********************
#include "suckParticle.h"
#include "manager.h"
#include "suckeffect.h"

//=====================================
// オーバーロードコンストラクタ
//=====================================
CSuckParticle::CSuckParticle(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
}
//=====================================
// デストラクタ
//=====================================
CSuckParticle::~CSuckParticle()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CSuckParticle* CSuckParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife)
{
	// パーティクルのポインタを宣言
	CSuckParticle* pParticle = new CSuckParticle;

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
	pParticle->m_targetPos = targetPos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;

	// ポインタを返す
	return pParticle;
}
//=====================================
// 初期化処理
//=====================================
HRESULT CSuckParticle::Init(void)
{
	// 配列クリア
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CSuckParticle::Uninit(void)
{
	// 配列クリア
	m_pEffect.clear();

	// 親クラスの破棄
	CObject::Release();
}
//=====================================
// 更新処理
//=====================================
void CSuckParticle::Update(void)
{
	D3DXCOLOR col = m_col;
	D3DXVECTOR3 pos = m_pos;
	D3DXVECTOR3 targetPos = m_targetPos;

	for (int nCnt = 0; nCnt < m_nMaxParticle; nCnt++)
	{
		pos.x = pos.x + ((float)(rand() % 30) - 15.0f);
		pos.y = pos.y + ((float)(rand() % 60) - 30.0f);
		pos.z = pos.z + ((float)(rand() % 150) - 75.0f);

		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		float fRise = (float)(rand() % m_nLength) / 50.0f + 7.0f;

		// 寿命
		int nLife = ((rand() % m_nLife) + 10);

		// パーティクル生成
		CSuckEffect* pEffect = CSuckEffect::Create(pos, targetPos, col,VECTOR3_NULL, nLife, fRadius);

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
void CSuckParticle::Draw(void)
{
	// 無し
}
