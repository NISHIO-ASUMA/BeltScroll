//=========================================
//
// プレイヤー処理 [ player.cpp ]
// Author: Asuma Nishio
//
// TODO : ブロワーの処理入れる
// 
//=========================================

//**********************
// インクルードファイル
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "state.h"
#include "sound.h"
#include "enemy.h"
#include "effect.h"
#include "particlepiler.h"

//**********************
// 名前空間
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 5.0f;		 // 1フレームの移動量
	constexpr float JUMPVALUE = 19.0f;	 // ジャンプ量
	constexpr float GRAVITY = 0.7f;		 // 重力値
	constexpr float HITRADIUS = 25.0f;	 // 当たり判定の半径
	constexpr int   KeyRepeatCount = 15; // キーのリピート最大カウント
};

//**********************
// 静的メンバ変数宣言
//**********************
bool CPlayer::m_isDeath = false;  // 死亡フラグ

//===============================
// オーバーロードコンストラクタ
//===============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
	m_Scal = INITSCALE;
	m_State = NULL;
	m_nIdxTexture = NULL;
	m_rotDest = VECTOR3_NULL;
	m_nNumAll = NULL;
	m_type = NULL;
	m_posOld = VECTOR3_NULL;
	m_pFilename = {};
	m_nIdxPlayer = NULL;
	m_fAngle = NULL;
	m_fAvoidTime = NULL;

	// モデルのポインタのクリア
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// クラスポインタ
	m_pMotion = nullptr;
	m_pShadowS = nullptr;
	m_pStateMachine = nullptr;

	// フラグメント
	m_isLanding = false;
	m_isJump = false;
	m_isAttack = false;
	m_isMoving = false;
}
//===============================
// デストラクタ
//===============================
CPlayer::~CPlayer()
{
	// 無し
}
//===============================
// プレイヤー生成処理
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife, const char* pFilename)
{
	// プレイヤーのインスタンス生成
	CPlayer* pPlayer = new CPlayer;

	// インスタンスがnullptrだったら
	if (pPlayer == nullptr) return nullptr;

	// オブジェクト設定
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->m_pFilename = pFilename;

	// プレイヤー初期化処理
	if (FAILED(pPlayer->Init()))
	{
		// nullptrを返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}
//===============================
// プレイヤー初期化処理
//===============================
HRESULT CPlayer::Init(void)
{
	// オブジェクトの種類をセット
	SetObjType(TYPE_PLAYER);

	// モデル総数を代入
	m_nNumAll = MAX_MODEL;

	// モーション種類数を代入
	m_type = PLAYERMOTION_MAX;

	// フラグを設定
	m_isDeath = false;
	m_isJump = false;
	m_isLanding = false;
	m_isMoving = false;

	// モーションの読み込み
	m_pMotion = CMotion::Load(m_pFilename, MAX_MODEL, m_apModel,PLAYERMOTION_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(PLAYERMOTION_MAX);

	// プレイヤー識別モデルフラグを設定
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// nullptrじゃなかったら
		if (m_apModel[nCnt] != nullptr)
		{
			// フラグを設定する
			m_apModel[nCnt]->SetIsPlayer(true);
		}
	}
	
	// ステンシルシャドウ生成
	m_pShadowS = CShadowS::Create
	(
		m_pos, 
		m_rot
	);
	

	// ステートマシンを生成
	m_pStateMachine = new CStateMachine;

	// 初期状態をセット
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// 結果を返す
	return S_OK;
}
//===============================
// プレイヤー終了処理
//===============================
void CPlayer::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		// nullptrチェック
		if (m_apModel[nCnt] != nullptr)
		{
			// 終了処理
			m_apModel[nCnt]->Uninit();

			// ポインタの破棄
			delete m_apModel[nCnt];

			// nullptrにする
			m_apModel[nCnt] = nullptr;
		}
	}

	// nullptrチェック
	if (m_pMotion != nullptr)
	{
		// ポインタの破棄
		delete m_pMotion;

		// nullptrにする
		m_pMotion = nullptr;
	}

	// nullptrチェック
	if (m_pStateMachine != nullptr)
	{
		// 終了処理
		m_pStateMachine->OnExit();

		// ポインタの破棄
		delete m_pStateMachine;

		// nullptrにする
		m_pStateMachine = nullptr;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}
//============================================================
// プレイヤー更新処理
//============================================================
void CPlayer::Update(void)
{
	// 死んでるなら処理しない
	if (m_isDeath) return;

	// 入力デバイスのポインタ取得
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;

	pInput = CManager::GetInputKeyboard();
	pJoyPad = CManager::GetJoyPad();

	//// nullptrじゃないとき
	//if (m_pStateMachine != nullptr)
	//{
	//	// ステート更新
	//	m_pStateMachine->Update();
	//}

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

#if 1
	//=====================
	// 移動処理
	//=====================
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// Aキー

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// 左斜め上

			m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);

			// モーション変更
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// 右斜め下

			m_move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);

			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else
		{// 単体
			m_move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);

			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// Dキーを押した

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// Wキーを押した
			m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);

			// タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// Sキーを押した
			m_move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);

			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}
		else
		{// Dキーのみ押した
			m_move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);

			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_MOVE);
		}

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// Wキーを押した

		m_move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y - (D3DX_PI);

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// 角度を正規化
		if (m_rot.y < -D3DX_PI)
		{// D3DX_PIより小さくなったら
			m_rot.y += D3DX_PI * 2.0f;
		}

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// Sキーを押した

		m_move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y;

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE || !m_isJump)
		{
			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		}
	}

	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// 左回転
		// 角度
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// 右回転
		// 角度
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// 現在の角度
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;
#endif

	if (m_isJump == false)
	{// ジャンプしていなくて着地していないとき

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE))
		{
			m_isJump = true;
			m_isLanding = false;

			// ジャンプキーが押された
			m_move.y = PLAYERINFO::JUMPVALUE;
		}
	}

	// ジャンプが使われている
	if (m_isJump)
	{
		// モーション変更
		m_pMotion->SetMotion(PLAYERMOTION_JUMP);
	}

	// 着地時の処理
	if (m_isLanding)
	{
		// 着地モーションに変更
		// m_pMotion->SetMotion(PLAYERMOTION_LANDING);

		// ジャンプ可能状態に変更
		m_isJump = false;

		//// モーション終了時　かつ 種類が着地モーション
		//if (m_pMotion->GetMotionType() == PLAYERMOTION_LANDING && m_pMotion->GetFinishMotion())
		//{
		//	m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		//}
	}

	// Lキーで範囲攻撃
	if (CManager::GetInputKeyboard()->GetPress(DIK_L))
	{
		// 有効判定
		m_isAttack = true;

		// 吹き飛ばし
		EnemyBlow();

#ifdef _DEBUG
		// パーティクル生成
		CParticlePiler::Create(m_pos, D3DXCOLOR(0.12f, 1.0f, 0.03f, 1.0f), 20, 50.0f, 50.0f, 25, m_rot.y);
#endif // _DEBUG
	}

	// 重力加算
	m_move.y -= PLAYERINFO::GRAVITY;

	// 位置保存
	m_posOld = m_pos;

	// 位置更新
	m_pos += m_move;

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * 0.75f;
	m_move.z += (0.0f - m_move.z) * 0.75f;

	// 現在のy座標が0.0f以下の時
	if (m_pos.y <= 0.0f)
	{
		// y座標を地面の座標に設定
		m_pos.y = 0.0f;

		// 着地判定を有効化
		m_isLanding = true;

		// 高さへの移動量を0.0fに設定
		m_move.y = 0.0f;
	}

	// ステンシルシャドウが存在
	if (m_pShadowS)
	{
		// オブジェクト設定
		m_pShadowS->SetPos(D3DXVECTOR3(m_pos.x,0.0f,m_pos.z));
		m_pShadowS->SetRot(m_rot); 
	}

	// モーションの全体更新
	m_pMotion->Update(m_apModel, MAX_MODEL); 
}
//===============================
// プレイヤー描画処理
//===============================
void CPlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	// 識別描画
	CDebugproc::Print("プレイヤーの座標 { %.2f,%.2f,%.2f }", m_pos.x, m_pos.y, m_pos.z);
	// デバッグフォント描画
	CDebugproc::Draw(0, 120);

	// 識別描画
	CDebugproc::Print("プレイヤーの角度 { %.2f,%.2f,%.2f }", m_rot.x, m_rot.y, m_rot.z);

	// デバッグフォント描画
	CDebugproc::Draw(0, 140);

	// モーション描画
	CDebugproc::Print("MAINプレイヤーのモーション { %d } ", GetNowMotion());

	// デバッグフォント描画
	CDebugproc::Draw(0, 160);
}
//=========================================
// モデルの特定部分パーツの取得関数
//=========================================
CModel* CPlayer::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// プレイヤーが持っているモデルの数の中から探す
	for (int nModel = 0; nModel < MAX_MODEL; nModel++)
	{
		// モデルがある かつ 取得したい物と一致していたら
		if (m_apModel[nModel] && m_apModel[nModel]->GetPartType() == modelpart)
		{
			// 該当モデルのidx番号のモデルを返す
			return m_apModel[nModel];
		}
	}

	// 該当なし
	return nullptr;
}

//=========================================
// ステート変更
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// 自分自身を代入
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}

//=========================================
// 攻撃更新処理
//=========================================
void CPlayer::UpdateAction(CInputKeyboard* pInputKeyboard,D3DXMATRIX pMtx,const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{

}

//=========================================
// 移動更新処理
//=========================================
void CPlayer::UpdateMove(CInputKeyboard* pInputKeyboard, CJoyPad* pPad)
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	//=====================
	// 移動処理
	//=====================
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// Aキー

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// 左斜め上

			m_move.x += sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.75f);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// 右斜め下

			m_move.x -= sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.25f);
		}
		else
		{// 単体
			m_move.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y + (D3DX_PI * 0.5f);
		}

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// Dキーを押した

		if (CManager::GetInputKeyboard()->GetPress(DIK_W))
		{// Wキーを押した
			m_move.x += sinf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.75f);
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
		{// Sキーを押した
			m_move.x -= sinf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_move.z -= cosf(pCamera->GetRot().y - D3DX_PI * 0.25f) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.25f);
		}
		else
		{// Dキーのみ押した
			m_move.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_move.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * PLAYERINFO::MOVE;
			m_rotDest.y = pCamera->GetRot().y - (D3DX_PI * 0.5f);
		}

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// Wキーを押した

		m_move.x += sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z += cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y - (D3DX_PI);

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		// 角度を正規化
		if (m_rot.y < -D3DX_PI)
		{// D3DX_PIより小さくなったら
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// Sキーを押した

		//　タイプ切り替え
		m_pMotion->SetMotion(PLAYERMOTION_MOVE);

		m_move.x -= sinf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_move.z -= cosf(pCamera->GetRot().y) * PLAYERINFO::MOVE;
		m_rotDest.y = pCamera->GetRot().y;

		// 角度の正規化
		if (m_rot.y > D3DX_PI)
		{// D3DX_PIより大きくなったら
			m_rot.y -= D3DX_PI * 2.0f;
		}
	}
	else
	{
		if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE)
		{
			//　タイプ切り替え
			m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, true, 10, false);
		}
	}

	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{// 左回転
		// 角度
		m_rot.y = m_rot.y + D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{// 右回転
		// 角度
		m_rot.y = m_rot.y - D3DX_PI * 2.0f;
	}

	// 現在の角度
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.25f;
}
//=========================================
// ジャンプ更新処理
//=========================================
void CPlayer::UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{

}
//=============================
// コリジョン処理関数
//=============================
void CPlayer::Collision(void)
{
#if 0

	// ダメージ中か確認
	if (GetStateMachine()->GetNowStateID() == CPlayerStateBase::ID_DAMAGE)
		return;

#endif
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// いずれかの移動キー入力
	return (pKeyInput->GetPress(DIK_A) 
		|| pKeyInput->GetPress(DIK_D)
		|| pKeyInput->GetPress(DIK_S)
		|| pKeyInput->GetPress(DIK_W));
}
//===============================
// キー押下時の入力取得
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// いずれかの移動キー入力
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
//===============================
// ジャンプ制御関数
//===============================
void CPlayer::StartJump(void)
{
	// ジャンプキー入力 かつ ジャンプフラグがfalseの時
	if (!m_isJump)
	{
		// フラグを有効化
		m_isJump = true;

		// 未着地判定に変更
		m_isLanding = false;

		// 上昇値を設定
		m_move.y = PLAYERINFO::JUMPVALUE;

		// 移動更新
		AddMove();
	}
}
//===============================
// 現在のモーション種類取得
//===============================
CPlayer::PLAYERMOTION CPlayer::GetNowMotion() const
{
	// nullじゃなかったら
	if (m_pMotion)
	{
		// 現在番号を返す
		return static_cast<CPlayer::PLAYERMOTION>(m_pMotion->GetMotionType());
	}

	return PLAYERMOTION_NEUTRAL; // デフォルト
}
//===============================
// ヒット処理
//===============================
void CPlayer::HitDamage(int nDamage)
{
#if 0
	// パラメーター取得
	int nHp = m_pParameter->GetHp();

	// 体力を減らす
	nHp -= nDamage;

	// 現在体力が0以下
	if (nHp <= NULL)
	{
		// 現在体力をセット
		m_pParameter->SetHp(nHp);

		// 死亡フラグをセット
		m_isDeath = true;

		// モーションセット
		m_pMotion->SetMotion(PLAYERMOTION_DAMAGE, false, 0, false);

		return;
	}
	else
	{
		// 現在体力をセット
		m_pParameter->SetHp(nHp);
	}

#endif
}
//=======================================
// 敵吹き飛ばし処理 ( 範囲をどうするか ) 距離減衰,集め方(まとめて投げるために)
//=======================================
void CPlayer::EnemyBlow(void)
{
	// 範囲と威力
	const float fBlowRange = 100.0f;	// 有効範囲
	const float fBlowPower = 50.0f;		// 吹き飛ばし強度

	// 敵オブジェクトの先頭取得
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	while (pObj != nullptr)
	{
		// 敵取得
		if (pObj->GetObjType() == CObject::TYPE_ENEMY)
		{
			// キャスト
			CEnemy* pEnemy = static_cast<CEnemy*>(pObj);

			// 敵座標取得
			D3DXVECTOR3 vEnemyPos = pEnemy->GetPos();

			// プレイヤーとの距離
			D3DXVECTOR3 vDiff = vEnemyPos - m_pos;

			float fDist = D3DXVec3Length(&vDiff);

			// 範囲内なら吹き飛ばし
			if (fDist < fBlowRange)
			{
				// 正規化
				D3DXVec3Normalize(&vDiff, &vDiff);

				// 吹き飛ばし方向
				D3DXVECTOR3 vBlow = vDiff * fBlowPower;

				// 敵側に速度を加える
				pEnemy->AddBlow(vBlow);
				pEnemy->SetBlow(true);
			}
		}

		// 次の敵を取得
		pObj = pObj->GetNext();
	}
}