//===================================
//
// ゴール地点処理 [ goal.cpp ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードガード
//******************************
#include "goal.h"

//====================================
// コンストラクタ
//====================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority), m_DestPos(VECTOR3_NULL), m_isGoal(false)
{
	// 値のクリア
}
//====================================
// デストラクタ
//====================================
CGoal::~CGoal()
{
	// 無し
}
//====================================
// 生成処理
//====================================
CGoal* CGoal::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CGoal* pGoal = new CGoal;
	if (pGoal == nullptr) return nullptr;

	// オブジェクト設定
	pGoal->SetPos(pos);
	pGoal->SetRot(VECTOR3_NULL);
	pGoal->SetFilePass("data/MODEL/STAGEOBJ/Goal.x");

	// 初期化失敗時
	if (FAILED(pGoal->Init())) 	return nullptr;

	return pGoal;
}
//====================================
// 初期化処理
//====================================
HRESULT CGoal::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 座標を格納する
	m_DestPos = GetPos();

	return S_OK;
}
//====================================
// 終了処理
//====================================
void CGoal::Uninit(void)
{
	// 親クラスの破棄
	CObjectX::Uninit();
}
//====================================
// 更新処理
//====================================
void CGoal::Update(void)
{
	// 親クラスの更新
	CObjectX::Update();
}
//====================================
// 描画処理
//====================================
void CGoal::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//====================================
// チェック処理
//====================================
bool CGoal::CheckPos(D3DXVECTOR3 pos)
{
	// 距離計算
	D3DXVECTOR3 diffpos = m_DestPos - pos;

	// 長さ計算
	float fLength = D3DXVec3Length(&diffpos);

	// 範囲内の座標に入っていたら
	if (fLength < 120.0f)
	{
		return true;
	}

	// 範囲外なら
	return false;
}