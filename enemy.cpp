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

//==============================
// コンストラクタ
//==============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority),
m_move(VECTOR3_NULL),
m_pShadowS(nullptr),
m_isBlow(false),
m_TrushType(TYPE_NONE),
m_pCollider(nullptr),
m_pAABB(nullptr),
m_nColorType(NULL)
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName,int nTrushType, int nColorType)
{
	// インスタンス生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr) return nullptr;

	// 値を代入
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);
	pEnemy->SetTrushMassType(nTrushType);
	pEnemy->SetColorType(nColorType);

	// 初期化失敗時
	if (FAILED(pEnemy->Init())) return nullptr;

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
	// m_pShadowS = CShadowS::Create(D3DXVECTOR3(GetPos().x, -5.0f, GetPos().z), GetRot());

	// 球コライダー生成
	m_pCollider = CSphereCollider::Create(GetPos(), 90.0f);

	// 矩形コライダー生成
	m_pAABB = CAABBCollider::Create(GetPos(), GetPos(), GetSize());

	// シャドウセット
	SetShadow(true);

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

	delete m_pAABB;
	m_pAABB = nullptr;

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
	m_move.y -= 1.5f;
	NowPos += m_move;

	if (NowPos.y <= 0.0f) 
		NowPos.y = 0.0f;

	// 敵の座標をセット
	SetPos(NowPos);

	// コライダー座標
	m_pCollider->SetPos(NowPos);
	m_pAABB->SetPos(NowPos);

	// 取得
	D3DXVECTOR3 UpdatePos = GetPos();

	// マップに配置されているブロックを取得 
	auto Block = CGame::GetGameManager()->GetBlockManager();
	if (Block == nullptr) return;

	// ブロックオブジェクトとの当たり判定
	for (int nBlock = 0; nBlock < Block->GetAll(); nBlock++)
	{
		// コライダー取得
		CAABBCollider* pCollider = Block->GetBlock(nBlock)->GetCollider();

		// 押し出し座標
		D3DXVECTOR3 OutPos = UpdatePos;

		// 実際のコリジョン
		if (CollisionToBlock(pCollider, &OutPos))
		{
			// 押し出す座標をセットする
			UpdatePos = OutPos;

			// 座標セット
			SetPos(UpdatePos);

			// 矩形コライダーの更新
			m_pAABB->SetPos(OutPos);
		}
	}

	// 当たり判定生成
	for (int nCnt = 0; nCnt < COLLOBJ; nCnt++)
	{
		// シュレッダーのコライダー取得
		auto ShredderCol = CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt)->GetCollider();

		if (Collision(ShredderCol))
		{
			// エフェクト生成
			CConfettiParticle::Create(GetPos(), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 40, 150, 500, 40, -D3DX_PI * 0.5f);
			CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt)->AddTrush(m_nColorType);

			// 自身の消去
			this->Uninit();

			// 影も消す
			// m_pShadowS->Uninit();
			
			// 下の処理を通さない
			return;
		}
	}

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;

	//// ステンシル更新
	//if (m_pShadowS)
	//{
	//	m_pShadowS->SetPos(D3DXVECTOR3(GetPos().x, -5.0f, GetPos().z));
	//	m_pShadowS->SetRot(GetRot());
	//}
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
//=======================================
// 配置されているブロックとの当たり判定
//=======================================
bool CEnemy::CollisionToBlock(CAABBCollider* pOther, D3DXVECTOR3* pOutPos)
{
	return CAABBAABBCollision::CollisionT(m_pAABB,pOther,pOutPos);
}