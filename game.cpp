//=====================================
//
// メインゲーム処理 [ game.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "game.h"
#include "manager.h"
#include "debugproc.h"
#include "title.h"
#include "result.h"
#include "meshfield.h"
#include <memory>
#include "goal.h"
#include "player.h"

//**************************
// 定数空間
//**************************
namespace GAMEINFO
{
	constexpr int GAMECOUNT = 30; // リザルト遷移カウント
};

//**************************
// 静的メンバ変数宣言
//**************************
CPauseManager* CGame::m_pPausemanager = nullptr; // ポーズマネージャーのポインタ
CGameManager* CGame::m_pGameManager = nullptr;	// ゲームマネージャーのポインタ

//==================================
// コンストラクタ
//==================================
CGame::CGame() : CScene(CScene::MODE_GAME),m_nGametype(GAMESTATE_NONE),m_nStateCount(NULL)
{
	// 値のクリア
}
//==================================
// デストラクタ
//==================================
CGame::~CGame()
{
	// 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CGame::Init(void)
{
	// ポーズマネージャー生成
	m_pPausemanager = new CPauseManager;

	// nullだったら
	if (m_pPausemanager == nullptr)
	{
		return E_FAIL;
	}

	// ポーズマネージャー初期化処理
	m_pPausemanager->Init();

	// マネージャー生成
	m_pGameManager = new CGameManager;
	m_pGameManager->Init();

	// 通常進行状態
	m_nGametype = GAMESTATE_NORMAL;


	// 初期化結果を返す
	return S_OK;
}
//==================================
// 終了処理
//==================================
void CGame::Uninit(void)
{
	// nullチェック
	if (m_pPausemanager != nullptr)
	{
		// 終了処理
		m_pPausemanager->Uninit();

		// ポインタの破棄
		delete m_pPausemanager;

		// nullptrにする
		m_pPausemanager = nullptr;
	}

	// nullチェック
	if (m_pGameManager != nullptr)
	{
		// 終了処理
		m_pGameManager->Uninit();

		// ポインタの破棄
		delete m_pGameManager;

		// nullptrにする
		m_pGameManager = nullptr;
	}
}
//==================================
// 更新処理
//==================================
void CGame::Update(void)
{	
	// ポーズのキー入力判定
	m_pPausemanager->SetEnablePause();
	
	// ポーズの更新処理
	m_pPausemanager->Update();
	
	// フェード取得
	CFade* pFade = CManager::GetFade();

	switch (m_nGametype)
	{
	case GAMESTATE_NORMAL://通常状態
		break;

	case GAMESTATE_END:
		m_nStateCount++;

		if (m_nStateCount >= 30)
		{
			// カウンターを初期化
			m_nStateCount = 0;
			
			// 1秒経過
			m_nGametype = GAMESTATE_NONE;//何もしていない状態

			// フェードが取得できたら
			if (pFade != nullptr)
			{
				// リザルトシーンに遷移
				pFade->SetFade(std::make_unique<CResult>());

				// ここで処理を返す
				return;
			}
		}
		break;

	case GAMESTATE_LOSEEND:
		m_nStateCount++;

		if (m_nStateCount >= GAMEINFO::GAMECOUNT)
		{
			// カウンターを初期化
			m_nStateCount = 0;

			// 1秒経過
			m_nGametype = GAMESTATE_NONE;

			// フェードが取得できたら
			if (pFade != nullptr)
			{
				//// 負けリザルトシーンに遷移
				//pFade->SetFade(new CLoseResult());

				// ここで処理を返す
				return;
			}
		}
		break;
	}

	// falseの時に更新
	if (m_nGametype == GAMESTATE_NORMAL &&
		m_pPausemanager->GetPause() == false)
	{
		// ゲームマネージャー更新
		m_pGameManager->Update();

		// ゴール取得
		auto Goal = m_pGameManager->GetGoal();
		if (Goal == nullptr) return;

		// プレイヤー取得
		auto Player = m_pGameManager->GetPlayer();
		if (Player == nullptr) return;

		// 範囲内にいるか判定
		if (Goal->CheckPos(Player->GetPos()))
		{
			// タイプ変更
			m_nGametype = GAMESTATE_END;

			// プレイヤーの動きを止める
			Player->SetMove(VECTOR3_NULL);
			return;
		}

		//// 経過時間を取得
		//int Numtime = m_pGameManager->GetTime()->GetAllTime();

		//// タイマーが0秒以下なら
		//if (Numtime <= 0)
		//{
		//	// 負けリザルト遷移
		//	m_nGametype = GAMESTATE_LOSEEND;
		//	return;
		//}

		// 状態変更
		// m_nGametype = GAMESTATE_END;
	}
}
//==================================
// 描画処理
//==================================
void CGame::Draw(void)
{
	// 無し
}
//==================================
// コンストラクタ
//==================================
CGame* CGame::Create(void)
{	
	// インスタンス生成
	CGame* pGame = new CGame;

	// nullptrだったら
	if (pGame == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pGame->Init()))
	{
		// ポインタを返す
		return nullptr;
	}

	// 生成されたポインタを返す
	return pGame;
}