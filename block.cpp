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

//================================
// オーバーロードコンストラクタ
//================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
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
HRESULT CBlock::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	return S_OK;
}
//================================
// 終了処理
//================================
void CBlock::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CBlock::Update(void)
{
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
// 当たり判定
//================================
bool CBlock::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// 当たらない時
	return false;
}