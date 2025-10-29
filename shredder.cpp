//=====================================
//
// シュレッダー処理 [ shredder.cpp ]
// Author: Asuma Nishio
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

//===============================
// コンストラクタ
//===============================
CShredder::CShredder(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
	m_pAABB = nullptr;
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
	pShredder->SetRot(VECTOR3_NULL);
	pShredder->m_nType = nType;

	switch (nType)
	{
	case CShredderManager::TYPE_RED:
		pShredder->SetFilePass("data/MODEL/STAGEOBJ/Red.x");
		break;
	case CShredderManager::TYPE_GREEN:
		pShredder->SetFilePass("data/MODEL/STAGEOBJ/Green.x");
		break;
	}

	// 初期化失敗時
	if (FAILED(pShredder->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pShredder;
}
//===============================
// 初期化処理
//===============================
HRESULT CShredder::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 矩形コライダー生成
	m_pAABB = CAABBCollider::Create(GetPos(), GetSize());

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredder::Uninit(void)
{
	// 破棄
	delete m_pAABB;
	m_pAABB = nullptr;

	// 親クラスの終了処理
	CObjectX::Uninit();
}
//===============================
// 更新処理
//===============================
void CShredder::Update(void)
{
	// 位置
	D3DXVECTOR3 pos = GetPos();

	CGameManager* pGameManager = CGame::GetGameManager();
	CPlayer* pPlayer = pGameManager->GetPlayer();
	D3DXVECTOR3 pPos = pPlayer->GetPos();
	D3DXVECTOR3 pPosOld = pPlayer->GetOldPos();

	CCamera* pCamera = CManager::GetCamera();

	if (pCamera->GetMove())
	{
		pos.x += pPos.x - pPosOld.x;
		SetPos(pos);
	}

	// 座標更新
	m_pAABB->SetPos(pos);
}
//===============================
// 描画処理
//===============================
void CShredder::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}

//===============================
// Z軸だけを動かしたいとき
//===============================
void CShredder::SetPosZ(float posZ)
{
	D3DXVECTOR3 pos = GetPos();
	pos.z = posZ;
	SetPos(pos);
}