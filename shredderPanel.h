//=====================================
//
// シュレッダーのパネル処理 [ shredderPanel.h ]
// Author: Soichiro Sasaki
//
//=====================================

#ifndef _SHREDDERPANEL_H_ // このマクロ定義がされてなかったら
#define _SHREDDERPANEL_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//**********************
// 前方宣言
//**********************
class CObject;
class CObject3D;

//**********************
// 動く床クラスを定義
//**********************
class CShredderPanel : public CObjectX
{
public:
	typedef enum
	{
		STATE_NORMAL=0,
		STATE_FLASH
	}STATE;
	// コンストラクタ・デストラクタ
	CShredderPanel(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CShredderPanel();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Flash(void);

	// セッター
	void SetPos(D3DXVECTOR3 pos);
	void SetState(int nState) { m_nState = nState; }

	// ゲッター
	D3DXVECTOR3 GetPos(void);

	// 静的メンバ関数
	static CShredderPanel* Create(D3DXVECTOR3 pos,int nType);

private:
	CObject3D* m_pPanel;		// パネル
	int m_nType;				// 種類
	int m_nFlachCnt;			// 点滅のカウント
	int m_nState;
	static constexpr float object3D_offset = 4.0f;
};

#endif