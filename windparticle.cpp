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
m_pEffect{}
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
CWindParticle* CWindParticle::Create(const D3DXVECTOR3 pos)
{
	// インスタンス生成
	CWindParticle* pWind = new CWindParticle;
	if (pWind == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pWind->Init())) return nullptr;


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

}
//===========================
// 更新処理
//===========================
void CWindParticle::Update(void)
{

}
//===========================
// 描画処理
//===========================
void CWindParticle::Draw(void)
{

}