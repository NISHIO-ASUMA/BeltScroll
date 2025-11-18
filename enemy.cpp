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
m_vSuckDir(VECTOR3_NULL),
m_pShadowS(nullptr),
m_pCollider(nullptr),
m_pAABB(nullptr),
m_isBlow(false),
m_isSuck(false),
m_nColorType(NULL),
m_TrushType(TYPE_NONE)
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
	// 球コライダーの破棄
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}

	// 矩形コライダーの破棄
	if (m_pAABB)
	{
		delete m_pAABB;
		m_pAABB = nullptr;
	}

	// 影を未使用にする
	SetShadow(false);

	// 親クラスの終了処理
	CObjectX::Uninit();
}
//==============================
// 更新処理
//==============================
void CEnemy::Update(void)
{

	// 現在シーン取得
	CScene::MODE nMode = CManager::GetScene();
	if (nMode != CScene::MODE_GAME) return;

	// プレイヤー取得
	CPlayer* pPlayer = CGame::GetGameManager()->GetPlayer();
	if (pPlayer == nullptr) return;

	// 座標取得
	D3DXVECTOR3 NowPos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 吸い込み中処理
	if (m_isSuck)
	{
		// 回転しながら中心に引き寄せられる
		m_vSuckDir *= 1.1f; // 徐々に加速
		NowPos += m_vSuckDir * 0.3f; // 吸い込み速度

		// 回転
		rot.x += 0.25f;
		rot.y += 0.35f;
		rot.z += 0.15f;

		SetRot(rot);
		SetPos(NowPos);

		m_pCollider->SetPos(NowPos);
		m_pAABB->SetPos(NowPos);

		if (D3DXVec3Length(&m_vSuckDir) > 90.0f) // 吸い込み終わり判定
		{
			// エフェクト生成
			CConfettiParticle::Create
			(
				D3DXVECTOR3(GetPos().x + 60.0f,GetPos().y,GetPos().z),
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				40, 150, 500, 40, -D3DX_PI * 0.5f
			);

			this->Uninit();

			return;
		}
		return; // 吸い込み中は他処理スキップ
	}

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
		auto pShredder = CGame::GetGameManager()->GetShredderM()->GetShredder(nCnt);

		if (Collision(ShredderCol))
		{
			m_isSuck = true;

			// 吸い込み方向をシュレッダーに設定
			D3DXVECTOR3 shredderPos = pShredder->GetPos();
			shredderPos.x += 50.0f;   // 少し右側

			m_vSuckDir = shredderPos - GetPos();
			D3DXVec3Normalize(&m_vSuckDir, &m_vSuckDir);

			// シュレッダーにゴミ登録
			pShredder->AddTrush(m_nColorType);
			m_vSuckDir *= 2.0f;

			// ランダムな回転
			rot.x = (rand() % 360) * D3DX_PI / 180.0f;
			rot.y = (rand() % 360) * D3DX_PI / 180.0f;
			rot.z = (rand() % 360) * D3DX_PI / 180.0f;
			SetRot(rot);

			return;
		}
	}

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.25f;
	m_move.z += (0.0f - m_move.z) * 0.25f;
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