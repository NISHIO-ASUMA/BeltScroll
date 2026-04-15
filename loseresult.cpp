//=========================================================
//
// 負けリザルトシーン処理 [ loseresult.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "loseresult.h"
#include "ui.h"
#include "manager.h"
#include "fade.h"
#include "ranking.h"
#include "loseplayer.h"
#include "meshfield.h"
#include "resultobject.h"
#include "resultenemy.h"

//=========================================================
// コンストラクタ
//=========================================================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT), m_pResultBlock(nullptr),
m_pResultEnemy(nullptr)
{
	
}
//=========================================================
// デストラクタ
//=========================================================
CLoseResult::~CLoseResult()
{

}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CLoseResult::Init(void)
{
	// カメラ初期化
	CCamera* pCamera = CManager::GetCamera();
	pCamera->Init();

	// メッシュフィールド生成
	CMeshField::Create(VECTOR3_NULL, 3100.0f, 2000.0f, 1, 1);

	// 負けリザルトプレイヤー生成
	CLosePlayer::Create(D3DXVECTOR3(0.0f,0.0f,-500.0f));

	// 負けの敵配置
	m_pResultEnemy = new CResultEnemy;
	m_pResultEnemy->Init("data/JSON/LoseResultEnemy.json");

	// リザルトブロック生成
	m_pResultBlock = new CResultBlock;
	m_pResultBlock->Init("data/JSON/ResultMap.json");

	//負けリザルトのBGM再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_RESULTLOSEBGM);

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CLoseResult::Uninit(void)
{
	// ポインタの破棄
	if (m_pResultEnemy)
	{
		m_pResultEnemy->Uninit();
		delete m_pResultEnemy;
		m_pResultEnemy = nullptr;
	}

	// ポインタの破棄
	if (m_pResultBlock)
	{
		m_pResultBlock->Uninit();
		delete m_pResultBlock;
		m_pResultBlock = nullptr;
	}
}
//=========================================================
// 更新処理
//=========================================================
void CLoseResult::Update(void)
{
	// キー入力で遷移
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// 画面遷移
		pFade->SetFade(std::make_unique<CRanking>());

		return;
	}
}
//=========================================================
// 描画処理
//=========================================================
void CLoseResult::Draw(void)
{
	// 無し
}