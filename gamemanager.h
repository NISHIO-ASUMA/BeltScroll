//======================================================
//
// ゲームシーンオブジェクト管理処理 [ gamemanager.h ]
// Author: Asuma Nishio
//
//======================================================

#ifndef _GAMEMANAGER_H_ // このマクロ定義がされてなかったら
#define _GAMEMANAGER_H_ // 2重インクルード防止のマクロ定義

//**************************
// 前方宣言
//**************************
class CBlockManager;
class CPlayer;

//**************************
// ゲーム管理クラスを定義
//**************************
class CGameManager
{
public:
	// コンストラクタ・デストラクタ
	CGameManager();
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CPlayer* GetPlayer(void) { return m_pPlayer; }

private:
	CBlockManager* m_pBlockManager; // ブロックマネージャー
	CPlayer* m_pPlayer;				// プレイヤー
};

#endif