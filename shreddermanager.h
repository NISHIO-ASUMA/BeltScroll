//======================================================
//
// シュレッダーマネージャー処理 [ shreddermanager.h ]
// Author: Asuma Nishio
//
//======================================================

#ifndef _SHREDDERMANAGER_H_ // このマクロ定義がされてなかったら
#define _SHREDDERMANAGER_H_ // 2重インクルード防止のマクロ定義

//**************************
// 前方宣言
//**************************
class CShredder;
class CShredbinManager;

//******************************
// シュレッダー管理クラスを定義
//******************************
class CShredderManager
{
public:
	typedef enum
	{// 種類
		TYPE_RED = 0,
		TYPE_BLUE,
		TYPE_MAX
	}TYPE;

	typedef enum
	{// 状態
		STATE_MOVE = 0,
		STATE_DUSTBOX,
		STATE_CRASH,
	}STATE;

	// コンストラクタ・デストラクタ
	CShredderManager();
	~CShredderManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Swap(void);
	void State(void);
	void TrushBox(void);

	// ゲッター
	CShredder* GetShredder(const int nIdx) { return m_pShredder[nIdx]; }
	STATE GetState(void) { return m_state; }
	D3DXVECTOR3 GetTrushBoxPos(void);

private:
	CShredder* m_pShredder[2];	// ポインタ
	int m_nSwapCnt;				// 入れ替えるカウント
	int m_nStateCnt;			// 状態管理のカウント
	bool m_bRedFlont;			// 赤いほうが手前にあるか
	bool m_isSaveScoreTrush;	// ボーナスを書き出したかどうか
	STATE m_state;				// 状態
	int m_trushBoxCnt;			// ごみステーションのカウント

	static constexpr int SWAPCOUNT = 300;
	static constexpr int LAST_TRASH_NUMBER = 2;
	static constexpr float FIXED_Z00 = -250.0f;
	static constexpr float FIXED_Z01 = 250.0f;

	static constexpr float DUSTBOX_X00 = 0.0f;
	static constexpr float DUSTBOX_X01 = 100.0f;
	static constexpr float DUSTBOX_X02 = 300.0f;

};

#endif