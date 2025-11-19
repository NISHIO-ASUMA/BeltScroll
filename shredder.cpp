//=====================================
//
// シュレッダー処理 [ shredder.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "shredder.h"
#include "game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "shreddermanager.h"
#include "collider.h"
#include "collision.h"
#include "model.h"
#include "suckParticle.h"
#include "shredbinmanager.h"
#include "combo.h"
#include "score.h"

//===============================
// コンストラクタ
//===============================
CShredder::CShredder(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_move = VECTOR3_NULL;
	m_oldPos = VECTOR3_NULL;
	m_offsetPos = VECTOR3_NULL;

	m_nType = NULL;
	m_nShredbin = NULL;
	m_fCnt = 0.0f;
	
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	m_pAABB = nullptr;
	m_pShredbinManager = nullptr;
}
//===============================
// デストラクタ
//===============================
CShredder::~CShredder()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CShredder* CShredder::Create(D3DXVECTOR3 pos,int nType)
{
	// インスタンス生成
	CShredder* pShredder = new CShredder;
	if (pShredder == nullptr) return nullptr;

	// オブジェクト設定
	pShredder->SetPos(pos);
	pShredder->m_offsetPos = pos;
	pShredder->m_nType = nType;

	// 初期化失敗時
	if (FAILED(pShredder->Init())) return nullptr;

	// 生成されたポインタを返す
	return pShredder;
}
//===============================
// 初期化処理
//===============================
HRESULT CShredder::Init(void)
{
	// モデル初期化
	InitModel();

	// モデルの向きを合わせるため
	m_rot.y = D3DX_PI;

	// 矩形コライダー生成
	m_pAABB = CAABBCollider::Create(m_pos, m_oldPos,D3DXVECTOR3(100.0f,300.0f,500.0f));
	m_pShredbinManager = new CShredbinManager;
	m_pShredbinManager->SetMove(D3DXVECTOR3(1.0f,0.0f,0.0f));
	m_pShredbinManager->SetType(m_nType);
	m_pShredbinManager->Init();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredder::Uninit(void)
{
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = nullptr;
	}

	// 破棄
	delete m_pAABB;
	m_pAABB = nullptr;

	// 破棄
	if (m_pShredbinManager != nullptr)
	{
		m_pShredbinManager->Uninit();
		delete m_pShredbinManager;
		m_pShredbinManager = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//===============================
// 更新処理
//===============================
void CShredder::Update(void)
{
	// シュレッダーの更新
	m_oldPos = m_offsetPos;
	m_offsetPos += m_move;

	// コライダー座標の更新
	m_pAABB->SetPos(m_offsetPos);
	m_pAABB->SetOldPos(m_oldPos);

	// モデルの更新
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Update();
	}

	UpdateModel();

	// 間違えたら揺れる
	Shake();

	m_pShredbinManager->Update();
	m_pShredbinManager->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 170.0f, m_pos.z));

	// パーティクル生成
	CSuckParticle::Create(D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y, m_pos.z), m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), 7, 30, 20, 20);
}

//===============================
// 描画処理
//===============================
void CShredder::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
//===============================
// コリジョン
//===============================
bool CShredder::Collision(CAABBCollider* pOther, D3DXVECTOR3* pOutPos)
{
	return CAABBAABBCollision::Collision(m_pAABB,pOther,pOutPos);
}

//===============================
// モデルの初期化処理
//===============================
void CShredder::InitModel(void)
{
	// タイプごとに違う部分
	switch (m_nType)
	{
	case CShredderManager::TYPE_RED:
		m_apModel[0] = CModel::Create(VECTOR3_NULL, 
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
									"data/MODEL/STAGEOBJ/shredder(RED)frame.x");
		break;
	case CShredderManager::TYPE_BLUE:
		m_apModel[0] = CModel::Create(VECTOR3_NULL,
									D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
									"data/MODEL/STAGEOBJ/shredder(BRUE)frame.x");
		break;
	}


	// 共通部分
	m_apModel[1] = CModel::Create(VECTOR3_NULL,
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		"data/MODEL/STAGEOBJ/shredderblade.x");
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[1]->OffSetPos(VECTOR3_NULL);
}

//===============================
// パーツの動き更新y
//===============================
void CShredder::UpdateModel(void)
{
	// 刃を回す処理
	D3DXVECTOR3 rot = m_apModel[1]->GetRot();
	rot.z += 0.5f;
	m_apModel[1]->SetRot(rot);

	D3DXVECTOR3 pos = m_apModel[1]->GetPos();

	pos.y = -30.0f + sinf(m_fCnt) * 50.0f;
	m_fCnt += 0.07f;
	m_apModel[1]->SetPos(pos);
}

//===============================
// Z軸だけを動かしたいとき
//===============================
void CShredder::SetPosZ(float posZ)
{
	m_offsetPos.z = posZ;
}

//===============================
// シュレッダービンにごみ追加
//===============================
void CShredder::AddTrush(int nType)
{
	m_nShredbin = m_pShredbinManager->GetNumAll();
	// 種類一致時
	if (m_nType == nType)
	{
		// ゴミ量を加算
		m_nShredbin += BIN_AMOUNT;

		// コンボ加算
		CCombo::Add(100);

		// スコアを加算 ( コンボ値 * 基底スコア値 )
		CScore::Add(1000 * CCombo::GetCombo());
	}
	else
	{
		m_nShake = 30;
		// コンボリセット
		CCombo::Reset();
	}

	m_pShredbinManager->SetNum(m_nShredbin);
}

//===============================
// 間違えた時の振動
//===============================
void CShredder::Shake(void)
{
	if (m_nShake > 0)
	{
		m_pos.x = m_offsetPos.x + sinf((float)m_nShake) * 12.0f;
		m_pos.y = m_offsetPos.y + sinf((float)m_nShake) * 12.0f;
		m_pos.z = m_offsetPos.z + sinf((float)m_nShake) * 12.0f;
	}
	else if(m_nShake <= 0)
	{
		m_pos = m_offsetPos;
	}
	m_nShake--;
}