//=============================================
//
// 勝利プレイヤー処理 [ winplayer.h ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// インクルードファイル宣言
//**************************
#include "winplayer.h"
#include "motion.h"
#include "model.h"
#include "manager.h"
#include "shadowS.h"

//================================
// コンストラクタ
//================================
CWinPlayer::CWinPlayer(int nPriority) : CObject(nPriority),
m_apModel{},
m_pFilename{},
m_pMotion{},
m_pShadowS{},
m_pos(VECTOR3_NULL),
m_rot(VECTOR3_NULL),
m_rotDest(VECTOR3_NULL),
m_mtxworld{},
m_Scal(INITSCALE)
{

}
//================================
// デストラクタ
//================================
CWinPlayer::~CWinPlayer()
{

}
//================================
// 生成処理
//================================
CWinPlayer* CWinPlayer::Create(D3DXVECTOR3 pos)
{
	CWinPlayer* winplayer = new CWinPlayer;
	if (winplayer == nullptr) return nullptr;

	winplayer->m_pos = pos;
	winplayer->m_rot = VECTOR3_NULL;
	winplayer->m_pFilename = "data/MOTION/Player/WinPlayer.txt";

	if (FAILED(winplayer->Init()))
	return nullptr;

	return winplayer;
}
//================================
// 初期化処理
//================================
HRESULT CWinPlayer::Init(void)
{
	// モーション読み込み
	m_pMotion = CMotion::Load(m_pFilename, WIN_MODEL, m_apModel, WINMOTION_MAX);
	m_pMotion->SetMotionNum(WINMOTION_MAX);

	// ステンシルシャドウ生成
	m_pShadowS = CShadowS::Create
	(
		m_pos,
		m_rot
	);

	// 初期モーションセット
	m_pMotion->SetMotion(WINMOTION_ACTION);

	return S_OK;
}
//================================
// 終了処理
//================================
void CWinPlayer::Uninit(void)
{
	for (auto& model : m_apModel)
	{
		if (model != nullptr)
		{
			model->Uninit();

			delete model;

			model = nullptr;
		}
	}

	if (m_pMotion)
	{
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	CObject::Release();

}
//================================
// 更新処理
//================================
void CWinPlayer::Update(void)
{
	// ステンシルシャドウが存在
	if (m_pShadowS)
	{
		// オブジェクト設定
		m_pShadowS->SetPos(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z));
		m_pShadowS->SetRot(m_rot);
	}

	// モーション更新
	m_pMotion->Update(m_apModel, WIN_MODEL);
}
//================================
// 描画処理
//================================
void CWinPlayer::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScal, m_Scal.x, m_Scal.y, m_Scal.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < WIN_MODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}