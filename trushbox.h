//=====================================
//
// ごみステーション処理 [ trushbox.h ]
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
class CTrushBox : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CTrushBox(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CTrushBox();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTrushBox* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pScriptName);

private:
	static constexpr int nNumParts = 2;
};