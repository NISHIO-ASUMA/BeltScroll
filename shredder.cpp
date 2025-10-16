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

//===============================
// コンストラクタ
//===============================
CShredder::CShredder(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
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
CShredder* CShredder::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CShredder* pShredder = new CShredder;
	if (pShredder == nullptr) return nullptr;

	// オブジェクト設定
	pShredder->SetPos(pos);
	pShredder->SetRot(VECTOR3_NULL);
	pShredder->SetFilePass("data/MODEL/STAGEOBJ/Shredder.x");

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

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CShredder::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//===============================
// 更新処理
//===============================
void CShredder::Update(void)
{
	// 無し
}
//===============================
// 描画処理
//===============================
void CShredder::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
