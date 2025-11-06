//==================================================
//
// 敵の処理 [ enemy.cpp ]
// Author: Asuma Nishio
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
#include "shreddermanager.h"
#include "shredder.h"
#include "score.h"
#include "confettieffect.h"
#include "confettiparticle.h"
#include "blockmanager.h"
#include "combo.h"

//==============================
// コンストラクタ
//==============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_move(VECTOR3_NULL),
m_pShadowS(nullptr),
m_isBlow(false),
m_TrushType(TYPE_NONE),
m_pCollider(nullptr),
m_nType(0)
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName,int nType)
{
	// インスタンス生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// 値を代入
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);
	pEnemy->SetType(nType);

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

	// 球コライダー生成
	m_pCollider = CSphereCollider::Create(GetPos(), 85.0f);

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CEnemy::Uninit(void)
{
	// コライダーの破棄
	delete m_pCollider;
	m_pCollider = nullptr;

	// 親クラスの終了処理
	CObjectX::Uninit();
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

	// ブロワーの種類取得
	int nBlowerType = pPlayer->GetBlowType();

	// 現在のブロワーの種類に応じて飛ぶ敵かどうかを判断
	if (m_TrushType <= nBlowerType)
	{
		// 以下または同等
		float friction = 0.92f;
		m_move *= friction;
	}
	else
	{
		// それ以上の敵
		float friction = 0.65f;
		m_move *= friction;
	}

	if (D3DXVec3Length(&m_move) < 0.0f)
	{
		m_isBlow = false;
		m_move = VECTOR3_NULL;
	}
	
	// 座標の更新
	m_move.y -= 0.5f;
	NowPos += m_move;

	if (NowPos.y <= 0.0f) 
		NowPos.y = 0.0f;

	// コライダー座標
	m_pCollider->SetPos(NowPos);

	// 当たり判定生成
	for (int nCnt = 0; nCnt < COLLOBJ; nCnt++)
	{
		// シュレッダーのコライダー取得
		auto ShredderCol = CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt)->GetCollider();

		if (Collision(ShredderCol))
		{
			// エフェクト生成
			CConfettiParticle::Create(GetPos(), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 40, 150, 500, 40, -D3DX_PI * 0.5f);
			CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt)->AddTrush(m_nType);
			// コンボ加算
			CCombo::Add(100);

			// 自身の消去
			this->Uninit();

			// 影も消す
			m_pShadowS->Uninit();
			
			// 下の処理を通さない
			return;
		}
	}

	// TODO : 今度考える
	//// マップに配置されているブロックを取得 
	//auto Block = CGame::GetGameManager()->GetBlockManager();
	//if (Block == nullptr) return;

	//// ブロックオブジェクトとの当たり判定
	//for (int nBlock = 0; nBlock < Block->GetAll(); nBlock++)
	//{
	//	// コライダー取得
	//	CAABBCollider* pCollider = Block->GetBlock(nBlock)->GetCollider();

	//	// 実際のコリジョン
	//	if (Collision(pCollider))
	//	{

	//	}
	//}

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	// 座標をセット
	SetPos(NowPos);

	// ステンシル更新
	if (m_pShadowS)
	{
		m_pShadowS->SetPos(D3DXVECTOR3(GetPos().x, -2.0f, GetPos().z));
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
bool CEnemy::Collision(CAABBCollider* pOtherCollider)
{
	// 判定結果を返す
	return CAABBSphereCollision::CollisionT(pOtherCollider, m_pCollider);
}