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
class CEnemyManager;
class CTrushSim;
class CShredderManager;
class CGoal;
class CScore;

//**************************
// インクルードファイル
//**************************
#include <memory>

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
	CTrushSim* GetTrush(void) { return m_pTrushSim; }
	CGoal* GetGoal(void) { return m_pGoal; }
	CShredderManager* GetShredderM(void) { return m_pShredderManaher; }
	CBlockManager* GetBlockManager(void) { return m_pBlockManager; }
	CEnemyManager* GetEnemyManager(void) { return m_pEnemyManager.get(); }
	CScore* GetScore(void) {return m_pScore;}

private:
	std::unique_ptr<CEnemyManager>m_pEnemyManager; // 敵管理
	CBlockManager* m_pBlockManager; // ブロックマネージャー
	CPlayer* m_pPlayer;				// プレイヤー
	CTrushSim* m_pTrushSim;			// 試し
	CShredderManager* m_pShredderManaher;// シュレッダーマネージャー
	CGoal* m_pGoal;					// ゴールクラス
	CScore* m_pScore;				// ゲームのスコア
};

#endif