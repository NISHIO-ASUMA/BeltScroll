//==================================================
//
// 敵の処理 [ enemy.cpp ]
// Author: Asuma Nishio
//
// 
// TODO : 矩形と球が出来次第、コライダー変更する
// 
//==================================================

//******************************
// インクルードファイル
//******************************
#include "enemy.h"
#include "shadow.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"
#include "game.h"
#include "shadowS.h"
#include "collider.h"
#include "collision.h"

//==============================
// コンストラクタ
//==============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_move(VECTOR3_NULL),
m_pShadowS(nullptr),
m_isBlow(false),
m_TrushType(TYPE_NONE),
m_pCollider(nullptr)
{
	// 値のクリア
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
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);

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
	// 親クラスの初期化
	CObjectX::Init();

	// オブジェクトの種類をセット
	SetObjType(TYPE_ENEMY);

	// ステンシルシャドウの生成
	m_pShadowS = CShadowS::Create(D3DXVECTOR3(GetPos().x, 0.0f, GetPos().z), GetRot());

	// コライダー生成
	m_pCollider = CSphereCollider::Create(GetPos(), 30.0f);

	// 移動量をセット
	m_move.x = 5.0f;
	m_move.z = 5.0f;

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CEnemy::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();

	// コライダーの破棄
	delete m_pCollider;
	m_pCollider = nullptr;
}
//==============================
// 更新処理
//==============================
void CEnemy::Update(void)
{
	// プレイヤー取得
	CPlayer* pPlayer = CGame::GetGameManager()->GetPlayer();
	if (pPlayer == nullptr) return;

	// 座標取得
	D3DXVECTOR3 NowPos = GetPos();

	// プレイヤーに向かってくる処理
	D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤー位置取得
	D3DXVECTOR3 dir = playerPos - NowPos;		// プレイヤーへのベクトル
	float dist = D3DXVec3Length(&dir);			// 距離

	D3DXVec3Normalize(&dir, &dir);	// 正規化
	float speed = 2.0f;				// 追従スピード
	m_move += dir * speed;			// 移動ベクトルに加算

	// 吹き飛ばしが有効の時
	if (m_isBlow)
	{
		// 摩擦係数を計算する
		m_move *= 0.9f; // 減速

		if (D3DXVec3Length(&m_move) < 0.05f)
		{
			m_isBlow = false;
			m_move = VECTOR3_NULL;
		}
	}

	// 重力値
	m_move.y -= 0.5f;

	// 位置更新
	NowPos += m_move;
	
	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	if (NowPos.y <= 0.0f)
	{
		NowPos.y = 0.0f;
	}

	// 座標セット
	SetPos(NowPos);

	 // ステンシルシャドウが存在
	if (m_pShadowS)
	{
		// オブジェクト設定
		m_pShadowS->SetPos(D3DXVECTOR3(GetPos().x,0.0f, GetPos().z));
		m_pShadowS->SetRot(GetRot());
	}
}
//==============================
// 描画処理
//==============================
void CEnemy::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//==============================
// 当たり判定処理
//==============================
bool CEnemy::Collision(CSphereCollider* pOtherCollider)
{
	// 判定結果を返す
	return CSphereSphereCollision::Collision(m_pCollider, pOtherCollider);
}
