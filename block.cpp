//=====================================
//
// ブロック処理 [ block.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "block.h"
#include "collider.h"
#include "collision.h"

//================================
// オーバーロードコンストラクタ
//================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_pAABB = nullptr;
}
//================================
// デストラクタ
//================================
CBlock::~CBlock()
{
	// 無し
}
//================================
// 生成処理
//================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// インスタンス生成
	CBlock* pBlock = new CBlock;
	if (pBlock == nullptr) return nullptr;

	// オブジェクト設定
	pBlock->SetFilePass(FileName);
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->SetScale(Scale);

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
HRESULT CBlock::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// AABBコライダー生成
	m_pAABB = CAABBCollider::Create(GetPos(), GetPos(), GetSize());

	return S_OK;
}
//================================
// 終了処理
//================================
void CBlock::Uninit(void)
{
	// ポインタの破棄
	if (m_pAABB)
	{
		delete m_pAABB;
		m_pAABB = nullptr;
	}

	// 親クラスの終了
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CBlock::Update(void)
{
	// 座標取得
	D3DXVECTOR3 pos = GetPos();

	// コライダー座標更新
	m_pAABB->SetPos(pos);

	// 親クラスの更新
	CObjectX::Update();
}
//================================
// 描画処理
//================================
void CBlock::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}
//================================
// 矩形の当たり判定
//================================
bool CBlock::Collision(CAABBCollider* pOther, D3DXVECTOR3* pOutPos)
{
	// 矩形の当たり判定を返す
	return CAABBAABBCollision::CollisionT(m_pAABB,pOther, pOutPos);
}