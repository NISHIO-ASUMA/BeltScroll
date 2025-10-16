//=====================================
//
// 動く床処理 [ gimmickfloor.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "gimmickfloor.h"

//================================
// オーバーロードコンストラクタ
//================================
CGimmickFloor::CGimmickFloor(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
}
//================================
// デストラクタ
//================================
CGimmickFloor::~CGimmickFloor()
{
	// 無し
}
//================================
// 生成処理
//================================
CGimmickFloor* CGimmickFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// インスタンス生成
	CGimmickFloor* pBlock = new CGimmickFloor;
	if (pBlock == nullptr) return nullptr;

	// オブジェクト設定
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(Scale);
	pBlock->SetFilePass(FileName);

	// 初期化失敗時
	if (FAILED(pBlock->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタ
	return pBlock;
}
//================================
// 初期化処理
//================================
HRESULT CGimmickFloor::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	return S_OK;
}
//================================
// 終了処理
//================================
void CGimmickFloor::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CGimmickFloor::Update(void)
{
	// 動かす
	Move();

	// 親クラスの更新
	CObjectX::Update();
}
//================================
// 描画処理
//================================
void CGimmickFloor::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}

//================================
// 動かす処理
//================================
void CGimmickFloor::Move(void)
{
	// 位置取得
	D3DXVECTOR3 pos = CObjectX::GetPos();

	// サインでZ方向に動かす
	pos.z = sinf(m_fMoveCnt);

	// 反映
	CObjectX::SetPos(pos);
	
	// カウント
	m_fMoveCnt = COUNTSPEED;
}

//================================
// 当たり判定
//================================
bool CGimmickFloor::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// 当たらない時
	return false;
}