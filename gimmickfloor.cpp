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
#include "gamemanager.h"
#include "trushSim.h"
#include "game.h"
#include "collider.h"

//================================
// オーバーロードコンストラクタ
//================================
CGimmickFloor::CGimmickFloor(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_fMoveCnt = 0.0f;
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

	m_pCollider = CSphereCollider::Create(GetPos(), 20.0f);

	return S_OK;
}
//================================
// 終了処理
//================================
void CGimmickFloor::Uninit(void)
{

	delete m_pCollider;
	m_pCollider = nullptr;

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
	
	// あたり判定
	Collision();

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
	D3DXVECTOR3 rot = CObjectX::GetRot();
	rot.y += 0.01f;
	// 反映
	CObjectX::SetRot(rot);
}

//================================
// あたり判定処理
//================================
void CGimmickFloor::Collision(void)
{
	D3DXVECTOR3 vec[4];
	D3DXVECTOR3 vecTrush[4];

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXMATRIX mat = GetMtxWorld();

	D3DXVECTOR3 size = GetSize();

	size.x = (size.x * 0.5f) * 1.414f;
	size.y = (size.y * 0.5f);
	size.z = (size.z * 0.5f) * 1.414f;

	CGameManager* pManager = CGame::GetGameManager();
	CTrushSim* pTrush = pManager->GetTrush();
	D3DXMATRIX trushMat = pTrush->GetMtxWorld();
	D3DXVECTOR3 trushPos = pTrush->GetPos();
	D3DXVECTOR3 trushPosOld = pTrush->GetPosOld();

	D3DXVECTOR3 ePos[4];

	ePos[0].x = pos.x + sinf(rot.y + (D3DX_PI * 0.25f)) * size.x;
	ePos[0].z = pos.z + cosf(rot.y + (D3DX_PI * 0.25f)) * size.z;
	ePos[1].x = pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * size.x;
	ePos[1].z = pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * size.z;
	ePos[2].x = pos.x + sinf(rot.y - (D3DX_PI * 0.75f)) * size.x;
	ePos[2].z = pos.z + cosf(rot.y - (D3DX_PI * 0.75f)) * size.z;
	ePos[3].x = pos.x + sinf(rot.y - (D3DX_PI * 0.25f)) * size.x;
	ePos[3].z = pos.z + cosf(rot.y - (D3DX_PI * 0.25f)) * size.z;

	vec[0].x = ePos[1].x - ePos[0].x;
	vec[0].z = ePos[1].z - ePos[0].z;
	vec[1].x = ePos[2].x - ePos[1].x;
	vec[1].z = ePos[2].z - ePos[1].z;
	vec[2].x = ePos[3].x - ePos[2].x;
	vec[2].z = ePos[3].z - ePos[2].z;
	vec[3].x = ePos[0].x - ePos[3].x;
	vec[3].z = ePos[0].z - ePos[3].z;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		vec[nCnt].y = 0.0f;
		vecTrush[nCnt].y = 0.0f;
	}

	vecTrush[0].x = trushPos.x - ePos[0].x;
	vecTrush[0].z = trushPos.z - ePos[0].z;
	vecTrush[1].x = trushPos.x - ePos[1].x;
	vecTrush[1].z = trushPos.z - ePos[1].z;
	vecTrush[2].x = trushPos.x - ePos[2].x;
	vecTrush[2].z = trushPos.z - ePos[2].z;
	vecTrush[3].x = trushPos.x - ePos[3].x;
	vecTrush[3].z = trushPos.z - ePos[3].z;


	D3DXVECTOR3 nor[4];

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3Cross(&nor[nCnt], &vec[nCnt],&vecTrush[nCnt]);
	}

	D3DXVECTOR3 oldNor[4];

	vecTrush[0].x = trushPosOld.x - ePos[0].x;
	vecTrush[0].z = trushPosOld.z - ePos[0].z;
	vecTrush[1].x = trushPosOld.x - ePos[1].x;
	vecTrush[1].z = trushPosOld.z - ePos[1].z;
	vecTrush[2].x = trushPosOld.x - ePos[2].x;
	vecTrush[2].z = trushPosOld.z - ePos[2].z;
	vecTrush[3].x = trushPosOld.x - ePos[3].x;
	vecTrush[3].z = trushPosOld.z - ePos[3].z;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3Cross(&oldNor[nCnt], &vec[nCnt], &vecTrush[nCnt]);
	}

	if (nor[0].y > 1.0f && nor[1].y > 1.0f && nor[2].y > 1.0f && nor[3].y > 1.0f
		|| nor[0].y < 1.0f && nor[1].y < 1.0f && nor[2].y < 1.0f && nor[3].y < 1.0f)
	{
		if (trushPos.y - 15.0f < pos.y + size.y&& trushPosOld.y - 15.0f > pos.y + size.y)
		{

			D3DXVECTOR3 dir = trushPos - pos;

			float fRadius = D3DXVec3Length(&dir);

			float v = 0.01f * fRadius;

			D3DXVec3Normalize(&dir, &dir);

			trushPos.x += dir.z * v;
			trushPos.y = trushPosOld.y;
			trushPos.z += -dir.x * v;

			pTrush->SetPos(trushPos);
			pTrush->SetRot(rot);
			SetRot(rot);
		}
		else if (trushPos.y + 15.0f > pos.y - size.y && trushPosOld.y + 15.0f < pos.y - size.y)
		{
			trushPos.y = trushPosOld.y;
			pTrush->SetPos(trushPos);
		}
		else if(trushPos.y + 15.0f > pos.y - size.y && trushPos.y - 15.0f < pos.y - size.y||
			trushPos.y - 15.0f < pos.y + size.y && trushPos.y + 15.0f > pos.y + size.y)
		{
			trushPos.x = trushPosOld.x;
			trushPos.z = trushPosOld.z;
			pTrush->SetPos(trushPos);
		}

	}
}