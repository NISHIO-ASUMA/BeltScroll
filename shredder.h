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

//***************************
// シュレッダークラスを定義
//***************************
class CShredder : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CShredder(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CShredder();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void InitModel(void);
	void UpdateModel(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetPosZ(float posZ);
	CAABBCollider* GetCollider(void) { return m_pAABB; }

	// 静的メンバ関数
	static CShredder* Create(D3DXVECTOR3 pos,int nType);

private:
	static constexpr int nNumParts = 2;
	CModel* m_apModel[nNumParts];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
	D3DXVECTOR3 m_move; // 移動量
	int m_nType;		// 種類
	CAABBCollider* m_pAABB; // 矩形のコライダー
};