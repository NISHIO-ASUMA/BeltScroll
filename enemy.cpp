//===================================
//
// 敵の処理 [ enemy.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードファイル
//******************************
#include "enemy.h"
#include "shadow.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"

//==============================
// コンストラクタ
//==============================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_Oldpos = VECTOR3_NULL;
	m_move = VECTOR3_NULL;
	m_scale = INITSCALE;

	D3DXMatrixIdentity(&m_mtxworld);

	m_pScriptName = nullptr;
	m_pShadow = nullptr;
	m_pMotion = nullptr;

	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}
//==============================
// デストラクタ
//==============================
CEnemy::~CEnemy()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName)
{
	// インスタンス生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// 値を代入
	pEnemy->m_pos = pos;
	pEnemy->m_rot = rot;
	pEnemy->m_pScriptName = pScriptName;

	// 初期化失敗時
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	// 生成されたインスタンスを返す
	return pEnemy;
}
//==============================
// 初期化処理
//==============================
HRESULT CEnemy::Init(void)
{
	// オブジェクトの種類をセット
	SetObjType(TYPE_ENEMY);

	// ポインタ生成
	m_pMotion = CMotion::Load(m_pScriptName, ENEMY_MODEL, m_pModel, ENEMYMOTION_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(ENEMYMOTION_MAX);

	// シャドウ生成
	m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x,2.0f,m_pos.z), m_rot);

	// 移動量をセット
	m_move.x = 3.0f;
	m_move.z = 3.0f;

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CEnemy::Uninit(void)
{
	// nullチェック
	if (m_pMotion != nullptr)
	{
		// 破棄
		delete m_pMotion;

		// null初期化
		m_pMotion = nullptr;
	}

	// 使用したモデル数の破棄
	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		// nullチェック
		if (m_pModel[nCnt] != nullptr)
		{
			// 終了処理
			m_pModel[nCnt]->Uninit();

			// 破棄
			delete m_pModel[nCnt];

			// null初期化
			m_pModel[nCnt] = nullptr;
		}
	}

	// 自身の破棄
	CObject::Release();
}
//==============================
// 更新処理
//==============================
void CEnemy::Update(void)
{
	// プレイヤー取得
	CPlayer* pPlayer = CGameManager::GetInstance()->GetPlayer();
	if (pPlayer == nullptr) return;

	// プレイヤーに向かってくる処理
	D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤー位置取得
	D3DXVECTOR3 dir = playerPos - m_pos;		// プレイヤーへのベクトル
	float dist = D3DXVec3Length(&dir);			// 距離

	D3DXVec3Normalize(&dir, &dir);			// 正規化
	float speed = 0.6f;						// 追従スピード
	m_move += dir * speed;					// 移動ベクトルに加算

	// 過去の位置情報を保存
	m_Oldpos = m_pos;

	// 位置更新
	m_pos += m_move;

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	 // ステンシルシャドウが存在
	if (m_pShadow)
	{
		// オブジェクト設定
		m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 2.0f, m_pos.z));
		m_pShadow->SetRot(m_rot);
	}

	// モーション更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_pModel, ENEMY_MODEL);
	}
}
//==============================
// 描画処理
//==============================
void CEnemy::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScal, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < ENEMY_MODEL; nCnt++)
	{
		m_pModel[nCnt]->Draw();
	}
}