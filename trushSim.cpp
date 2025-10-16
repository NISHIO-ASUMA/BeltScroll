//=====================================
//
// 動く床処理 [ gimmickfloor.cpp ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "trushSim.h"
#include "manager.h"
#include "input.h"

//================================
// オーバーロードコンストラクタ
//================================
CTrushSim::CTrushSim(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_posOld = VECTOR3_NULL;
}
//================================
// デストラクタ
//================================
CTrushSim::~CTrushSim()
{
	// 無し
}
//================================
// 生成処理
//================================
CTrushSim* CTrushSim::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, const char* FileName)
{
	// インスタンス生成
	CTrushSim* pBlock = new CTrushSim;
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
HRESULT CTrushSim::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	return S_OK;
}
//================================
// 終了処理
//================================
void CTrushSim::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CTrushSim::Update(void)
{
	// 操作
	Controll();

	// 親クラスの更新
	CObjectX::Update();
}
//================================
// 描画処理
//================================
void CTrushSim::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}

//================================
// 動かす処理
//================================
void CTrushSim::Controll(void)
{
	// 位置と向き取得
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 rot = CObjectX::GetRot();
	// 入力とカメラ取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	CCamera* pCamera = CManager::GetCamera();

	if (pKeyboard->GetPress(DIK_UP))
	{// 奥側
		pos.x += sinf(pCamera->GetRot().y) * 0.1f;
		pos.z += cosf(pCamera->GetRot().y) * 0.1f;

	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{// 手前
		pos.x -= sinf(pCamera->GetRot().y) * 0.1f;
		pos.z -= cosf(pCamera->GetRot().y) * 0.1f;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{// 右方向
		pos.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 0.1f;
		pos.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * 0.1f;

	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{// 左方向
		pos.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * 0.1f;
		pos.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * 0.1f;

	}

	// 反映
	CObjectX::SetPos(pos);
}

//================================
// 当たり判定
//================================
bool CTrushSim::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fDestSize, bool& isLanding)
{
	// 当たらない時
	return false;
}