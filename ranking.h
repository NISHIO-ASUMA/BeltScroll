//=====================================
//
// ランキングシーン処理 [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKING_H_ // このマクロ定義がされてなかったら
#define _RANKING_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
#include "scene.h"
#include "rankingscore.h"

//******************************
// ランキングシーンクラスを定義
//******************************
class CRanking : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CRanking();
	~CRanking();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSort(void);
	void TxtLoad(const char* pFileName);
	void TxtSave(const char* pFileName);

	// 静的メンバ関数
	static CRanking* Create();

private:
	static constexpr int MAX_RANK = 5;
	static constexpr int MAX_RANKTEX = 2;

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_RANKTEX];		// テクスチャのポインタ
	static CRankingScore* m_Score[MAX_RANK];

	CNumber* m_apNumbers[8];								// 数字のポインタ
	int m_nNumData[MAX_RANK];								// 数字のデータ数
};

#endif