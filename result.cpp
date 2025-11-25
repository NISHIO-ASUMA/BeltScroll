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

//=================================
// オーバーロードコンストラクタ
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT), m_pResultEnemy(nullptr)
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
	CWinPlayer::Create(VECTOR3_NULL);

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 2000.0f, 2000.0f, 1, 1);

	// UI生成
	CUi::Create(D3DXVECTOR3(260.0f, 525.0f, 0.0f), 0, 180.0f, 60.0f, "score_logo_result.png", false);

	// リザルトのスコア生成
	CResultScore::Create(D3DXVECTOR3(960.0f,525.0f,0.0f),200.0f,80.0f);

	// 敵生成
	//m_pResultEnemy = new CResultEnemy;
	//m_pResultEnemy->Init();

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
}
//=================================
// 更新処理
//=================================
void CResult::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ランキング
		CManager::GetFade()->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//=================================
// 描画処理
//=================================
void CResult::Draw(void)
{
	// 無し
}