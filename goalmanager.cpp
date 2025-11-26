//========================================
//
// ゴール管理処理 [ goalmanager.h ]
// Author: Asuma Nishio
//
//========================================

//**********************
// インクルードファイル
//**********************
#include "goalmanager.h"
#include "goal.h"

//=========================================
// コンストラクタ
//=========================================
CGoalManager::CGoalManager() : m_pGoal{}
{

}
//=========================================
// デストラクタ
//=========================================
CGoalManager::~CGoalManager()
{

}
//=========================================
// 初期化処理
//=========================================
HRESULT CGoalManager::Init(void)
{
	// ゴールモデルの生成
	m_pGoal[0] = CGoal::Create(D3DXVECTOR3(5485.0f, 250.0f, 180.0f), "data/MODEL/STAGEOBJ/Gate_door.x"); // 奥
	m_pGoal[1] = CGoal::Create(D3DXVECTOR3(5485.0f, 250.0f, -140.0f), "data/MODEL/STAGEOBJ/Gate_door.x"); // 手前

	return S_OK;
}
//=========================================
// 終了処理
//=========================================
void CGoalManager::Uninit(void)
{

}
//=========================================
// 更新処理
//=========================================
void CGoalManager::Update(void)
{
	// シュレッダー側から取得する
	
	// ゴールができるなら
	// if ()
	
	// Z座標をずらす
	D3DXVECTOR3 pos = m_pGoal[0]->GetPos();
	D3DXVECTOR3 posfront = m_pGoal[1]->GetPos();

	// 一定距離移動したら停止

}