//=========================================================
//
// リザルトシーン処理 [ result.h ]
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
#include "scene.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CResultEnemy;
class CResultScoreManager;
class CResultBlock;

//*********************************************************
// リザルトシーンクラスを定義
//*********************************************************
class CResult : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CResult();
	~CResult();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultScoreManager* GetScore(void) { return m_pResultScoreManager; }

private:

	static CResultScoreManager* m_pResultScoreManager; // スコア管理クラス
	CResultEnemy* m_pResultEnemy; // リザルトの敵クラス
	CResultBlock* m_pResultBlock;
};
