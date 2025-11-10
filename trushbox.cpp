//==================================================
//
// ごみステーションの処理 [ trushbox.cpp ]
// Author: Soichiro Sasaki
// 
//==================================================

//******************************
// インクルードファイル
//******************************
#include "trushbox.h"

//==============================
// コンストラクタ
//==============================
CTrushBox::CTrushBox(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
}
//==============================
// デストラクタ
//==============================
CTrushBox::~CTrushBox()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CTrushBox* CTrushBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName)
{
	// インスタンス生成
	CTrushBox* pEnemy = new CTrushBox;
	if (pEnemy == nullptr) return nullptr;

	// 値を代入
	pEnemy->SetPos(pos);
	pEnemy->SetRot(rot);
	pEnemy->SetFilePass(pScriptName);

	// 初期化失敗時
	if (FAILED(pEnemy->Init())) return nullptr;

	// 生成されたインスタンスを返す
	return pEnemy;
}
//==============================
// 初期化処理
//==============================
HRESULT CTrushBox::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// オブジェクトの種類をセット
	SetObjType(TYPE_ENEMY);

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CTrushBox::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//==============================
// 更新処理
//==============================
void CTrushBox::Update(void)
{

}
//==============================
// 描画処理
//==============================
void CTrushBox::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}