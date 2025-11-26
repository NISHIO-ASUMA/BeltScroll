//=====================================
//
// サイレン処理 [ siren.cpp ]
// Author: Asuma Nishio
//
//=====================================

//***************************
// インクルードファイル
//***************************
#include "siren.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CSiren::CSiren(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_dwNumMat = NULL;
	m_nIdxTexture = NULL;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pTexture = nullptr;
	m_mtxWorld = {};
	m_isGoal = false;
}
//=============================
// デストラクタ
//=============================
CSiren::~CSiren()
{

}
//=============================
// 生成処理
//=============================
CSiren* CSiren::Create(const D3DXVECTOR3 pos)
{
	// インスタンス生成
	CSiren* pSiren = new CSiren;
	if (pSiren == nullptr) return nullptr;

	// オブジェクト設定
	pSiren->SetPos(pos);

	// 初期化失敗時
	if (FAILED(pSiren->Init())) return nullptr;

	return pSiren;
}
//=============================
// 初期化処理
//=============================
HRESULT CSiren::Init(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/STAGEOBJ/Goal_siren.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat = nullptr;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// テクスチャインデックス配列の動的確保
	m_pTexture = new int[m_dwNumMat];

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// テクスチャが読み込めたら
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			// テクスチャポインタ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			// テクスチャなし
			m_pTexture[nCntMat] = -1;
		}
	}

	m_rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);

	return S_OK;
}
//=============================
// 終了処理
//=============================
void CSiren::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// nullじゃなかったら
	if (m_pTexture != nullptr)
	{
		// ポインタの破棄
		delete m_pTexture;

		// nullptrにする
		m_pTexture = nullptr;
	}

	// オブジェクトの破棄
	CObject::Release();
}
//=============================
// 更新処理
//=============================
void CSiren::Update(void)
{
	// 無し
}
//=============================
// 描画処理
//=============================
void CSiren::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// 格納
		D3DMATERIAL9 mat = pMat[nCntMat].MatD3D;

		// 有効時
		if (m_isGoal)
		{
			// カラーを緑にする
			mat.Diffuse.a = 1.0f;
			mat.Diffuse.r = 0.0f;
			mat.Diffuse.g = 1.0f;
			mat.Diffuse.b = 0.0f;
		}

		// マテリアル設定
		pDevice->SetMaterial(&mat);

		// インデックスに応じて変更する
		if (m_pTexture[nCntMat] != -1)
		{
			// テクスチャ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			// テクスチャなし
			pDevice->SetTexture(0, nullptr);
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}