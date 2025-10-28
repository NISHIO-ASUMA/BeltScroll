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

//******************************
// シュレッダー管理クラスを定義
//******************************
class CShredderManager
{
public:
	typedef enum
	{
		TYPE_RED = 0,
		TYPE_GREEN,
	}TYPE;

	// コンストラクタ・デストラクタ
	CShredderManager();
	~CShredderManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Swap(void);

	// ゲッター
	CShredder* GetShredder(const int nIdx) { return m_pShredder[nIdx]; }

private:
	CShredder* m_pShredder[2];	// ポインタ
	int m_nSwapCnt;				// 入れ替えるカウント
	bool m_bRedFlont;			// 赤いほうが手前にあるか
	static constexpr int SWAPCOUNT = 300;
	static constexpr float FIXED_Z00 = -250.0f;
	static constexpr float FIXED_Z01 = 250.0f;
};

#endif