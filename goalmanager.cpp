//=========================================================
//
// ゴール管理処理 [ goalmanager.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "goalmanager.h"
#include "goal.h"
#include "game.h"
#include "siren.h"

//=========================================================
// コンストラクタ
//=========================================================
CGoalManager::CGoalManager() : m_pGoal{}
{

}
//=========================================================
// デストラクタ
//=========================================================
CGoalManager::~CGoalManager()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGoalManager::Init(void)
{
	// ゴールモデルの生成
	m_pGoal[0] = CGoal::Create(D3DXVECTOR3(5485.0f, 250.0f, 180.0f), "data/MODEL/STAGEOBJ/Gate_door.x"); // 奥
	m_pGoal[1] = CGoal::Create(D3DXVECTOR3(5485.0f, 250.0f, -140.0f), "data/MODEL/STAGEOBJ/Gate_door.x"); // 手前

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGoalManager::Uninit(void)
{

}
//=========================================================
// 更新処理
//=========================================================
void CGoalManager::Update(void)
{
	// シュレッダー側から取得する
	auto isGoal = CGame::GetGameManager()->GetSiren()->GetisFlags();
	if (isGoal == false) return;

	// ゴールができるなら
	if (isGoal)
	{
		// Z座標をずらしてドアを開ける
		D3DXVECTOR3 pos = m_pGoal[0]->GetPos();
		D3DXVECTOR3 posfront = m_pGoal[1]->GetPos();

		// 一定距離移動したら
		if (pos.z >= 420.0f)
		{
			// 座標を固定
			pos.z = 420.0f;

			// 座標セット
			m_pGoal[0]->SetPos(pos);
		}

		// 一定距離移動したら
		if (posfront.z <= -400.0f)
		{
			// 座標を固定
			posfront.z = -400.0f;

			// 座標セット
			m_pGoal[1]->SetPos(posfront);
		}

		// 座標移動
		pos.z += 2.0f;
		posfront.z -= 2.0f;

		// 座標セット
		m_pGoal[0]->SetPos(pos);
		m_pGoal[1]->SetPos(posfront);
	}
}