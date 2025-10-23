//=============================================
//
// 勝利プレイヤー処理 [ winplayer.h ]
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
// 勝ちキャラクタークラスを定義
//*******************************
class CWinPlayer : public CObject
{
public:
	//**************************
	// モーションの種類
	//**************************
	enum WINMOTION
	{
		WINMOTION_NEUTRAL, // 初期値
		WINMOTION_ACTION,  // アクション
		WINMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CWinPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CWinPlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成関数
	static CWinPlayer* Create(D3DXVECTOR3 pos);

private:
	static inline constexpr int WIN_MODEL = 16; // プレイヤーで使うモデルの数

	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_rotDest;  // 目的角
	D3DXVECTOR3 m_Scal;		// 拡大率
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[WIN_MODEL];	// 使うモデルのポインタ
	CMotion* m_pMotion;				// モーションのポインタ
	CShadowS* m_pShadowS;			// ステンシルシャドウクラスポインタ

	const char* m_pFilename; // 読み込むファイル名
};

