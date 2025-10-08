//======================================================
//
// ゲームシーンオブジェクト管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
//
//======================================================

//******************************
// インクルードファイル
//******************************
#include "gamemanager.h"
#include "meshfield.h"

//******************************
// 静的メンバ変数
//******************************
CGameManager* CGameManager::m_pInstance = nullptr;

//===============================
// デストラクタ
//===============================
CGameManager::~CGameManager()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CGameManager::Init(void)
{
	// TODO : 検証用生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CGameManager::Uninit(void)
{
	// インスタンスの破棄
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//===============================
// 更新処理
//===============================
void CGameManager::Update(void)
{

}
//===============================
// 描画処理
//===============================
void CGameManager::Draw(void)
{

}
//===============================
// インスタンス取得
//===============================
CGameManager* CGameManager::GetInstance(void)
{
	// インスタンスがnullなら
	if (m_pInstance == nullptr)
	{
		// ポインタ生成
		m_pInstance = new CGameManager();
	}

	// 生成ポインタを返す
	return m_pInstance;
}