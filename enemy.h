//===================================
//
// 敵の処理 [ enemy.h ]
// Author: Asuma Nishio
//
//===================================

//******************************
// インクルードガード
//******************************
#pragma once

//******************************
// インクルードファイル
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//******************************
// 前方宣言
//******************************
class CShadow;

//******************************
// 敵クラスを定義
//******************************
class CEnemy : public CObject
{
public:
	//***********************************
	// 敵が行うモーション列挙型
	//***********************************
	enum ENEMYMOTION
	{
		ENEMYMOTION_NEUTRAL,	// ニュートラル
		ENEMYMOTION_MAX
	};

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	static constexpr int ENEMY_MODEL = 1;

	D3DXVECTOR3 m_pos; // 座標
	D3DXVECTOR3 m_Oldpos; // 過去座標
	D3DXVECTOR3 m_rot; // 角度
	D3DXVECTOR3 m_scale; // 拡大率
	D3DXVECTOR3 m_move; // 移動量
	D3DXMATRIX m_mtxworld; // ワールドマトリックス

	CModel* m_pModel[ENEMY_MODEL]; // モデルポインタ
	CMotion* m_pMotion; // モーションポインタ
	CShadow* m_pShadow; // シャドウ
	const char* m_pScriptName; // モーションファイル名
};

