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
#include "shreddermanager.h"
#include "gamemanager.h"
#include "game.h"
#include "shredder.h"

int CShredbinEffect::m_nNum[2] = {};

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
	m_nType = 0;
	m_shredMove = VECTOR3_NULL;
	m_bBox = false;
}
//===============================
// デストラクタ
//===============================
CShredbinEffect::~CShredbinEffect()
{
}

//===============================
// 生成処理
//===============================
CShredbinEffect* CShredbinEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, float fRadius, int m_nType)
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
	pEffect->m_shredMove = move;
	pEffect->m_fRadius = fRadius;
	pEffect->m_size = size;
	pEffect->m_nType = m_nType;
	switch (m_nType)
	{
	case CShredderManager::TYPE_RED:
		pEffect->m_nIdx = m_nNum[CShredderManager::TYPE_RED];
		m_nNum[CShredderManager::TYPE_RED]++;
		break;
	case CShredderManager::TYPE_BLUE:
		pEffect->m_nIdx = m_nNum[CShredderManager::TYPE_BLUE];
		m_nNum[CShredderManager::TYPE_BLUE]++;
		break;
	}
	
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
	//カラーの設定
	D3DXCOLOR col = GetCol();

	// オブジェクト更新
	CBillboard::Update();

	D3DXVECTOR3 vec;

	m_oldPos = Effectpos;

	switch (CGame::GetGameManager()->GetShredderM()->GetState())
	{
	case CShredderManager::STATE_MOVE:
		BinUpdate();

		break;
	case CShredderManager::STATE_DUSTBOX:
		BoxUpdate();
		break;
	}


	// 0以下なら
	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// サイズセット
	SetSize(m_fRadius, m_fRadius);

	CGameManager* pGameManager = CGame::GetGameManager();
	CShredderManager* pShredManager = pGameManager->GetShredderM();
	CShredder* pShredder = pShredManager->GetShredder(m_nType);
	CShredbinManager* pBinManager = pShredder->GetShredbinManager();

	// 0以下の時
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_nIdx >= pBinManager->GetNumAll() && m_nType == nCnt)
		{
			m_nNum[nCnt]--;
			// 削除する
			Uninit();
		}
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

//=============================================
// シュレッダービンから出ないためのあたり判定
//=============================================
void CShredbinEffect::Collision(void)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_offsetPos.x + m_size.x * 0.5f <= pos.x /*&& m_offsetPos.x + m_size.x * 0.5f > m_oldPos.x*/
		|| m_offsetPos.x - m_size.x * 0.5f >= pos.x /*&& m_offsetPos.x - m_size.x * 0.5f < m_oldPos.x*/
		|| m_offsetPos.y + m_size.y * 0.5f <= pos.y /*&& m_offsetPos.y + m_size.y * 0.5f > m_oldPos.y*/
		|| m_offsetPos.y - m_size.y * 0.5f >= pos.y /*&& m_offsetPos.y - m_size.y * 0.5f < m_oldPos.y*/
		|| m_offsetPos.z + m_size.z * 0.5f <= pos.z /*&& m_offsetPos.z + m_size.z * 0.5f > m_oldPos.z*/
		|| m_offsetPos.z - m_size.z * 0.5f >= pos.z /*&& m_offsetPos.z - m_size.z * 0.5f < m_oldPos.z*/)
	{
		pos.x = m_offsetPos.x + m_size.x * (((float)(rand() % 80) - 40.0f) * 0.01f);
		pos.y = m_offsetPos.y + m_size.y * (((float)(rand() % 80) - 40.0f) * 0.01f);
		pos.z = m_offsetPos.z + m_size.z * (((float)(rand() % 80) - 40.0f) * 0.01f);

		D3DXVECTOR3 vecPos;

		vecPos.x = ((float)(rand() % 100) - 50.0f);
		vecPos.y = ((float)(rand() % 100) - 50.0f);
		vecPos.z = ((float)(rand() % 100) - 50.0f);

		D3DXVECTOR3 nor = vecPos - VECTOR3_NULL;
		D3DXVec3Normalize(&nor, &nor);
		m_move = nor * 1.5f;
	}

	SetPos(pos);
}


//=============================================
// シュレッダービン状態の更新
//=============================================
void CShredbinEffect::BinUpdate(void)
{
	// 座標,カラー取得
	D3DXVECTOR3 Effectpos = GetPos();

	// 移動量の更新
	Effectpos += m_move;
	Effectpos += m_shredMove;

	// 座標をセットする
	SetPos(Effectpos);

	GetManagerPosition();
	Collision();
}

//=============================================
// ごみステーション状態の更新
//=============================================
void CShredbinEffect::BoxUpdate(void)
{
	if (m_bBox == false && CGame::GetGameManager()->GetShredderM()->GetState() == CShredderManager::STATE_DUSTBOX)
	{// ごみステーション状態の初期化の役割
		m_move = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
		m_bBox = true;
	}

	// 座標,カラー取得
	D3DXVECTOR3 effectPos = GetPos();
	D3DXVECTOR3 posDest = CGame::GetGameManager()->GetShredderM()->GetTrushBoxPos();

	D3DXVECTOR3 vec = (posDest - effectPos);

	m_move.x = vec.x * 0.05f;
	m_move.y = vec.y * 0.01f;
	m_move.z = vec.z * 0.02f;

	// 移動量の更新
	effectPos += m_move;

	// 座標をセットする
	SetPos(effectPos);

	if (posDest == effectPos)
	{
		m_bBox = false;
	}
}

//=============================================
// オフセット位置情報の取得
//=============================================
void CShredbinEffect::GetManagerPosition(void)
{
	CGameManager* pGameManager = CGame::GetGameManager();
	CShredderManager* pShredManager = pGameManager->GetShredderM();
	CShredder* pShredder = pShredManager->GetShredder(m_nType);
	CShredbinManager* pBinManager = pShredder->GetShredbinManager();

	m_offsetPos = pBinManager->GetPos();
}