//==========================================
//
// リザルト用ゴミ箱処理 [ resulttrush.cpp ]
// Author: Asuma Nishio
//
// TODO : ボーナスの表示時間に合わせてパーティクル生成をする
// 
//==========================================

//****************************************
// インクルードファイル
//****************************************
#include "resulttrush.h"
#include "suckParticle.h"
#include "confettiparticle.h"
#include "result.h"
#include "resultscoremanager.h"
#include "resultscore.h"

//========================================
// コンストラクタ
//========================================
CResultTrush::CResultTrush(int nPriority) : CObjectX(nPriority),m_nParticleInterval(NULL),m_nParticleTimer(NULL),
m_nMaxTime(NULL), m_col(COLOR_WHITE)
{

}
//========================================
// 生成処理
//========================================
CResultTrush* CResultTrush::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXCOLOR col)
{
	CResultTrush* presult = new CResultTrush;
	if (presult == nullptr) return nullptr;

	// オブジェクト設定
	presult->SetPos(pos);
	presult->SetRot(rot);
	presult->SetCol(col);
	presult->SetFilePass("data/MODEL/STAGEOBJ/TrushBox.x");

	// 初期化失敗時
	if (FAILED(presult->Init())) return nullptr;

	return presult;
}
//========================================
// 初期化処理
//========================================
HRESULT CResultTrush::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 最大タイマー
	m_nMaxTime = 300;

	// 10フレームごとに生成する
	m_nParticleInterval = 30;

	return S_OK;
}
//========================================
// 終了処理
//========================================
void CResultTrush::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//========================================
// 更新処理
//========================================
void CResultTrush::Update(void)
{
	// 0になったら生成しない
	if (m_nMaxTime > 0)
	{
		// 減算
		m_nMaxTime--;

		m_nParticleTimer++;

		// 一定間隔でパーティクル生成
		if (m_nParticleTimer >= m_nParticleInterval)
		{
			m_nParticleTimer = 0;

			// パーティクル生成
			CConfettiParticle::Create
			(
				D3DXVECTOR3(GetPos().x, GetPos().y + 20.0f, GetPos().z),
				m_col,
				40, 150, 500, 40, D3DX_PI
			);
		}
	}
	else
	{
		m_nParticleTimer = NULL;
	}

	// 親クラスの更新
	CObjectX::Update();
}
//========================================
// 描画処理
//========================================
void CResultTrush::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}