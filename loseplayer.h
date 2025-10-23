//=============================================
//
// 敗北プレイヤー処理 [ loseplayer.h ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// インクルードガード
//**************************
#pragma once

//**************************
// インクルードファイル宣言
//**************************
#include "object.h"

//**********************
// 前方宣言
//**********************
class CInputKeyboard;
class CJoyPad;
class CShadowS;
class CModel;
class CMotion;

//*******************************
// 負けキャラクタークラスを定義
//*******************************
class CLosePlayer : public CObject
{
public:
	//**************************
	// モーションの種類
	//**************************
	enum LOSEMOTION
	{
		LOSEMOTION_NEUTRAL, // 初期値
		LOSEMOTION_ACTION,	// アクション
		LOSEMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CLosePlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CLosePlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 生成関数
	static CLosePlayer* Create(D3DXVECTOR3 pos);

private:

	static inline constexpr int LOSE_MODEL = 16; // プレイヤーで使うモデルの数

	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_rotDest;  // 目的角
	D3DXVECTOR3 m_Scal;		// 拡大率
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[LOSE_MODEL];	// 使うモデルのポインタ
	CMotion* m_pMotion;				// モーションのポインタ
	CShadowS* m_pShadowS;			// ステンシルシャドウクラスポインタ

	const char* m_pFilename; // 読み込むファイル名
};

