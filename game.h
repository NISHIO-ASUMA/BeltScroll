//====================================
//
// メインゲーム処理 [ game.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _GAME_H_ // このマクロ定義がされてなかったら
#define _GAME_H_ // 2重インクルード防止のマクロ定義

//****************************
// インクルードファイル宣言
//****************************
#include "scene.h"
#include "pausemanager.h"
#include "gamemanager.h"
#include "time.h"
#include <memory>

//****************************
// ゲームクラスを定義
//****************************
class CGame : public CScene
{
public:
	//***********************
	// ゲーム状態列挙型
	//***********************
	enum GAMESTATE
	{
		GAMESTATE_NONE,
		GAMESTATE_NORMAL,
		GAMESTATE_END,
		GAMESTATE_LOSEEND,
		GAMESTATE_MAX
	};

	// コンストラクタ・デストラクタ
	CGame();
	~CGame();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//　セッター
	void SetState(int state) { m_nGametype = state; }

	// 静的メンバ関数
	static CGame* Create(void);
	static CPauseManager* GetPause(void) { return m_pPausemanager; }
	static CGameManager* GetGameManager(void) { return m_pGameManager; }

private:
	static CPauseManager* m_pPausemanager;		// ポーズマネージャーポインタ
	static CGameManager* m_pGameManager;		// ゲームマネージャーポインタ

	int m_nGametype;
	int m_nStateCount;
};

#endif
