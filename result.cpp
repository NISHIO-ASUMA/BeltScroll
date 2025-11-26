//====================================
//
// リザルトシーン処理 [ result.cpp ]
// Author: Asuma Nishio
// 
//====================================

//**************************
// インクルードファイル宣言
//**************************
#include "result.h"
#include "ui.h"
#include "manager.h"
#include "ranking.h"
#include "winplayer.h"
#include "meshfield.h"
#include "ui.h"
#include "resultscore.h"
#include "resultenemy.h"
#include "resultscoremanager.h"

//=================================
// オーバーロードコンストラクタ
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT), m_pResultEnemy(nullptr), m_pResultScoreManager(nullptr)
{

}
//=================================
// デストラクタ
//=================================
CResult::~CResult()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CResult::Init(void)
{
	// カメラ初期化
	CCamera* pCamera = CManager::GetCamera();
	pCamera->Init();

	// 勝利プレイヤー生成
	CWinPlayer::Create(D3DXVECTOR3(80.0f,0.0f,-450.0f));

	// プレイヤーの右側にゴミ箱設置
	// 

	// そこにパーティクル生成
	
	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3100.0f, 2000.0f, 1, 1);

	// UI生成
	CUi::Create(D3DXVECTOR3(1050.0f, 360.0f, 0.0f), 0, 360.0f, 720.0f, "backboard.png", false);

	// リザルトのスコア生成
	// CResultScore::Create(D3DXVECTOR3(960.0f,525.0f,0.0f),200.0f,80.0f);

	// 敵生成
	m_pResultEnemy = new CResultEnemy;
	m_pResultEnemy->Init();

	// 管理クラス生成
	m_pResultScoreManager = new CResultScoreManager;
	m_pResultScoreManager->Init();

	// サウンド再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResult::Uninit(void)
{
	// ポインタの破棄
	if (m_pResultEnemy)
	{
		m_pResultEnemy->Uninit();
		delete m_pResultEnemy;
		m_pResultEnemy = nullptr;
	}

	// ポインタの破棄
	if (m_pResultScoreManager)
	{
		m_pResultScoreManager->Uninit();
		delete m_pResultScoreManager;
		m_pResultScoreManager = nullptr;
	}
}
//=================================
// 更新処理
//=================================
void CResult::Update(void)
{
	// 管理クラスの更新処理
	if (m_pResultScoreManager)
	{
		m_pResultScoreManager->Update();

	}
}
//=================================
// 描画処理
//=================================
void CResult::Draw(void)
{
	// 無し
}