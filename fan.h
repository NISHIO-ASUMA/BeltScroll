//========================================================
//
// 左においてある巨大ファンオブジェクト処理 [ fan.h ]
// Author: Asuma Nishio
//
//========================================================

//**********************
// インクルードガード
//**********************
#pragma once

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************
// 前方宣言
//**********************
class CModel;

//***********************************
// ファンオブジェクトクラスを定義
//***********************************
class CFan : public CObject
{
public:

	CFan(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CFan() = default;

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitModel(void);
	void UpdateModel(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	D3DXVECTOR3 GetPos(void) const { return m_pos; }

	static CFan* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pModelName);

private:

	static constexpr int nNumParts = 2;

	CModel* m_apModel[nNumParts];

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
	D3DXVECTOR3 m_offsetPos;// オフセットの位置
};