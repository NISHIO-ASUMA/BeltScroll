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
	// デストラクタ
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CPlayer* GetPlayer(void) { return m_pPlayer; }

	// 静的メンバ関数
	static CGameManager* GetInstance(void);

private:
	CGameManager() {}
	static CGameManager* m_pInstance; 	// シングルトン変数
	CBlockManager* m_pBlockManager;
	CPlayer* m_pPlayer;

};

#endif