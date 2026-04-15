//=========================================================
//
// ゴールライン処理 [ goalline.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "goalline.h"

//=========================================================
// コンストラクタ
//=========================================================
CGoalLine::CGoalLine(int nPriority) : CObjectX(nPriority), m_CheckPos(VECTOR3_NULL),m_isSet(false)
{
	
}
//=========================================================
// デストラクタ
//=========================================================
CGoalLine::~CGoalLine()
{

}
//=========================================================
// 生成処理
//=========================================================
CGoalLine* CGoalLine::Create(const D3DXVECTOR3 pos, const float fWidth)
{
	// インスタンス生成
	CGoalLine* pline = new CGoalLine;
	if (pline == nullptr) return nullptr;

	// オブジェクト設定
	pline->SetPos(pos);
	pline->SetRot(VECTOR3_NULL);
	pline->SetFilePass("data/MODEL/STAGEOBJ/GoalLine.x");

	// 初期化失敗時
	if (FAILED(pline->Init())) return nullptr;

	return pline;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CGoalLine::Init(void)
{
	// 親クラス初期化
	CObjectX::Init();

	// 目標座標を設定
	m_CheckPos = GetPos();

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CGoalLine::Uninit(void)
{
	// 親クラス終了処理
	CObjectX::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CGoalLine::Update(void)
{
	// 親クラス更新
	CObjectX::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CGoalLine::Draw(void)
{
	// 親クラス描画
	CObjectX::Draw();
}
//=========================================================
// 判定処理
//=========================================================
bool CGoalLine::CheckIsGoalPos(const D3DXVECTOR3 pos)
{
	// 距離計算
	D3DXVECTOR3 diffpos = m_CheckPos - pos;

	// 長さ計算
	float fLength = D3DXVec3Length(&diffpos);

	// 範囲内の座標に入っていたら
	if (fLength < 280.0f)
	{
		m_isSet = true;
		return true;
	}

	// 範囲外なら
	return false;
}