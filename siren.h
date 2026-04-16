//=========================================================
//
// サイレン処理 [ siren.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "object.h"

//*********************************************************
// サイレンオブジェクトクラスを定義
//*********************************************************
class CSiren : public CObject
{
public:

	CSiren(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CSiren();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSiren* Create(const D3DXVECTOR3 pos);

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMtxWorld(D3DXMATRIX mtxworld) { m_mtxWorld = mtxworld; }
	void SetIsGoalFlag(const bool isFlags) {m_isGoal = isFlags;}

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	bool GetisFlags(void) { return m_isGoal; }

private:

	LPD3DXMESH m_pMesh;			// メッシュ情報
	LPD3DXBUFFER m_pBuffMat;	// マテリアル情報
	DWORD m_dwNumMat;			// マテリアル数

	D3DXVECTOR3 m_pos;			// 座標
	D3DXVECTOR3 m_rot;			// 角度
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス

	int m_nIdxTexture;			// テクスチャインデックス
	int* m_pTexture;			// テクスチャポインタ
	bool m_isGoal;				// ゴール可能フラグ
};