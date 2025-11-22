//========================================================
//
// 左においてある巨大ファンオブジェクト処理 [ fan.cpp ]
// Author: Asuma Nishio
//
//========================================================

//**********************
// インクルードファイル
//**********************
#include "fan.h"
#include "model.h"
#include "template.h"
#include "manager.h"

//=======================
// コンストラクタ
//=======================
CFan::CFan(int nPriority) : CObject(nPriority), m_mtxworld{}
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_offsetPos = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
}
//=======================
// 初期化処理
//=======================
HRESULT CFan::Init(void)
{
	// モデル初期化
	InitModel();

	// NOTE : これはいらない..?
	// モデルの向きを合わせるため
	m_rot.y = D3DX_PI;

	return S_OK;
}
//=======================
// 終了処理
//=======================
void CFan::Uninit(void)
{
	// モデルの破棄
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = nullptr;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}
//=======================
// 更新処理
//=======================
void CFan::Update(void)
{
	// モデルの更新
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Update();
	}

	// 回転の更新
	UpdateModel();
}
//=======================
// 描画処理
//=======================
void CFan::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < nNumParts; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//=======================
// モデル初期化処理
//=======================
void CFan::InitModel(void)
{
	// ベース部分作成
	m_apModel[0] = CModel::Create(VECTOR3_NULL,VECTOR3_NULL,"data/MODEL/STAGEOBJ/fan_frame.x");

	// 回転する部分を作成
	m_apModel[1] = CModel::Create(VECTOR3_NULL,D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),"data/MODEL/STAGEOBJ/fan_wind.x");

	// 親設定
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[1]->OffSetPos(VECTOR3_NULL);
}
//=======================
// モデル更新処理
//=======================
void CFan::UpdateModel(void)
{
	// 中の回すモデルの角度
	D3DXVECTOR3 rot = m_apModel[1]->GetRot();
	rot.y += 0.3f;

	// 正規化する
	rot.y = NormalAngle(rot.y);

	// 角度適用
	m_apModel[1]->SetRot(rot);
}

//=======================
// 生成処理
//=======================
CFan* CFan::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pModelName)
{
	// インスタンス生成
	CFan* pFan = new CFan;
	if (pFan == nullptr) return nullptr;

	// オブジェクト設定
	pFan->SetPos(pos);
	pFan->m_offsetPos = pos;
	pFan->m_rot = rot;

	// 初期化失敗時
	if (FAILED(pFan->Init())) return nullptr;

	// ポインタを返す
	return pFan;
}