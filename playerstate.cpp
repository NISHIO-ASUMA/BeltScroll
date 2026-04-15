//=========================================================
//
// プレイヤー状態管理処理 [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "pausemanager.h"

//*********************************************************
// 定数宣言
//*********************************************************
namespace PLAYERSTATEINFO
{
	constexpr int DAMAGECOUNT = 40;	// 最大ステートカウント
}

//=========================================================
// プレイヤー状態コンストラクタ
//=========================================================
CPlayerStateBase::CPlayerStateBase()
{
	// 値のクリア
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//=========================================================
// プレイヤー状態デストラクタ
//=========================================================
CPlayerStateBase::~CPlayerStateBase()
{
	// 無し
}


//=========================================================
// 待機状態時コンストラクタ
//=========================================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// セット
	SetID(ID_NEUTRAL);
}
//=========================================================
// 待機状態時デストラクタ
//=========================================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// 無し
}
//=========================================================
// 待機状態開始関数
//=========================================================
void CPlayerStateNeutral::OnStart()
{
	// ニュートラルモーションに設定
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_NEUTRAL, true, 5, false);
}
//=========================================================
// 待機状態更新関数
//=========================================================
void CPlayerStateNeutral::OnUpdate()
{
	// キー入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// Damage中は一切入力を受け付けない
	if (m_pPlayer->GetStateMachine()->GetNowStateID() == ID_DAMAGE) return;

	// 移動入力があれば移動状態へ
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad) || pPad->GetLeftStick()))
	{
		// 状態変更
		m_pPlayer->ChangeState(new CPlayerStateMove, ID_MOVE);

		// ここで処理を返す
		return;
	}

	// 攻撃キー入力時
	if ((pInput->GetPress(DIK_RETURN) || pPad->GetPress(CJoyPad::JOYKEY_X)))
	{
		// ステート変更
		m_pPlayer->ChangeState(new CPlayerStateAction, ID_ACTION);

		// ここで処理を返す
		return;
	}

	// Spaceキー もしくは PadのAキー
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)))
		
	{
		// ステート変更
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}
}
//=========================================================
// 待機状態時終了関数
//=========================================================
void CPlayerStateNeutral::OnExit()
{
	// 無し
}

//=========================================================
// コンストラクタ
//=========================================================
CPlayerStateAction::CPlayerStateAction()
{
	// セット
	SetID(ID_ACTION);
}
//=========================================================
// デストラクタ
//=========================================================
CPlayerStateAction::~CPlayerStateAction()
{
	// 無し
}
//=========================================================
// 攻撃状態開始関数
//=========================================================
void CPlayerStateAction::OnStart()
{
}
//=========================================================
// 攻撃状態更新関数
//=========================================================
void CPlayerStateAction::OnUpdate()
{
}
//=========================================================
// 攻撃状態終了関数
//=========================================================
void CPlayerStateAction::OnExit()
{
	// 無し
}

//=========================================================
// 移動状態コンストラクタ
//=========================================================
CPlayerStateMove::CPlayerStateMove()
{
	// セット
	SetID(ID_MOVE);
}
//=========================================================
// 移動状態デストラクタ
//=========================================================
CPlayerStateMove::~CPlayerStateMove()
{
	// 無し
}
//=========================================================
// 移動状態開始関数
//=========================================================
void CPlayerStateMove::OnStart()
{
	// 無し
}
//=========================================================
// 移動状態更新関数
//=========================================================
void CPlayerStateMove::OnUpdate()
{
	// キー入力を取得	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// 移動処理実行
	m_pPlayer->UpdateMove(pInput, pPad);

	// キー入力が無い
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad))
	{
		// ニュートラルに遷移
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//=========================================================
// 移動状態終了関数
//=========================================================
void CPlayerStateMove::OnExit()
{
	// 無し
}

//=========================================================
// ジャンプ状態時コンスタラクタ
//=========================================================
CPlayerStateJump::CPlayerStateJump()
{
	// IDをセット
	SetID(ID_JUMP);
}
//=========================================================
// ジャンプ状態時デストラクタ
//=========================================================
CPlayerStateJump::~CPlayerStateJump()
{
	// 無し
}
//=========================================================
// ジャンプ状態時開始関数
//=========================================================
void CPlayerStateJump::OnStart()
{
	// ジャンプ開始
	m_pPlayer->StartJump();

	// ジャンプモーションに変更
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_JUMP);
}
//=========================================================
// ジャンプ状態時更新関数
//=========================================================
void CPlayerStateJump::OnUpdate()
{
}
//=========================================================
// ジャンプ状態時終了関数
//=========================================================
void CPlayerStateJump::OnExit()
{
	// 無し
}