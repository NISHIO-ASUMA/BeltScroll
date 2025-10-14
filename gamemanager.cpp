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
#include "ui.h"
#include "manager.h"
#include "result.h"
#include "player.h"

//******************************
// 静的メンバ変数
//******************************
CGameManager* CGameManager::m_pInstance = nullptr; // インスタンス

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
	//メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// プレイヤー生成 ( のちにモデル変更 )
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10,"data/MOTION/Player/Player100motion.txt");


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
	// キー入力
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// 遷移
		CManager::GetFade()->SetFade(new CResult());

		return;
	}
}
//===============================
// 描画処理
//===============================
void CGameManager::Draw(void)
{
	// 描画するものがあればここに追加
	// Object継承の物は書くな
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