//=====================================
//
// シュレッダー処理 [ shredder.h ]
// Author: Soichiro Sasaki
//
//=====================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CAABBCollider;
class CModel;
class CShredbinManager;

//***************************
// シュレッダークラスを定義
//***************************
class CShredder : public CObject
{
public:
	typedef enum
	{
		STATE_MOVE=0,
		STATE_DUSTBOX,
		STATE_CRASH,
	}STATE;

	// コンストラクタ・デストラクタ
	CShredder(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CShredder();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(CAABBCollider * pOther,D3DXVECTOR3 * pOutPos);

	void InitModel(void);
	void UpdateModel(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetPosZ(float posZ);
	void AddTrush(int nType);
	void State(void);

	CAABBCollider* GetCollider(void) { return m_pAABB; }
	CShredbinManager*GetShredbinManager(void){return m_pShredbinManager; }

	// 静的メンバ関数
	static CShredder* Create(D3DXVECTOR3 pos,int nType);

private:
	static constexpr int nNumParts = 2;

	CModel* m_apModel[nNumParts];

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
	D3DXVECTOR3 m_move; // 移動量
	D3DXVECTOR3 m_oldPos; // 過去の座標

	int m_nType;		// 種類
	int m_nShredbin;	// シュレッダービンに入ってるごみの量
	STATE m_state;		// 状態
	CAABBCollider* m_pAABB; // 矩形のコライダー
	CShredbinManager* m_pShredbinManager;
};