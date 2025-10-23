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
#include "collider.h"
#include "collision.h"

//================================
// オーバーロードコンストラクタ
//================================
CTrushSim::CTrushSim(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_posOld = VECTOR3_NULL;
	m_pCollider = nullptr;
	m_fJump = 0.0f;
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

	m_pCollider = CSphereCollider::Create(GetPos(), 20.0f);
	return S_OK;
}
//================================
// 終了処理
//================================
void CTrushSim::Uninit(void)
{
	delete m_pCollider;
	m_pCollider = nullptr;

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
	D3DXMATRIX mtx = GetMtxWorld();
	D3DXVECTOR3 pos;
	pos = CObjectX::GetPos();

	D3DXVECTOR3 rot = CObjectX::GetRot();
	// 入力とカメラ取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();
	CCamera* pCamera = CManager::GetCamera();

	m_posOld = pos;

	if (GetParent() != nullptr)
	{
		pos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
	}

	if (pKeyboard->GetPress(DIK_UP))
	{// 奥側
		pos.x += sinf(pCamera->GetRot().y) * SPEED;
		pos.z += cosf(pCamera->GetRot().y) * SPEED;

	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{// 手前
		pos.x -= sinf(pCamera->GetRot().y) * SPEED;
		pos.z -= cosf(pCamera->GetRot().y) * SPEED;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{// 右方向
		pos.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
		pos.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;

	}
	else if (pKeyboard->GetPress(DIK_LEFT))
	{// 左方向
		pos.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
		pos.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.5f) * SPEED;
	}
	else
	{
		pos = CObjectX::GetPos();
	}

	if (pKeyboard->GetTrigger(DIK_RSHIFT))
	{// 左方向
		m_fJump = JUMP;
	}

	if (GetParent() != nullptr)
	{
		CObjectX* parent = GetParent();
		D3DXMATRIX parentMtx = parent->GetMtxWorld();
		// 逆行列作成
		D3DXMATRIX invMtx;

		D3DXMatrixInverse(&invMtx, nullptr, &parentMtx);

		D3DXVECTOR3 wldPos = pos;
		D3DXVECTOR3 lclPos;

		D3DXVec3TransformCoord(&pos, &wldPos, &invMtx);
	}

	m_fJump -= 0.1f;

	pos.y += m_fJump;

	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
		m_fJump = 0.0f;
	}

	// 反映
	m_pCollider->SetPos(pos);
	CObjectX::SetPos(pos);
}

//================================
// 当たり判定
//================================
bool CTrushSim::Collision(CSphereCollider*pCollider)
{
	return CSphereSphereCollision::Collision(m_pCollider, pCollider);
}