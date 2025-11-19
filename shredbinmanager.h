//======================================================
//
// シュレッドビンマネージャー処理 [ shredbinmanager.h ]
// Author: Soichiro Sasaki
//
//======================================================

#ifndef _SHREDBINMANAGER_H_ // このマクロ定義がされてなかったら
#define _SHREDBINMANAGER_H_ // 2重インクルード防止のマクロ定義

//******************************
// シュレッダー管理クラスを定義
//******************************
class CShredbinManager
{
public:
	// コンストラクタ・デストラクタ
	CShredbinManager();
	~CShredbinManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetType(int nType) { m_nType = nType; }
	void SetNum(int nNum) { m_nNum[m_nType] = nNum; }

	// ゲッター
	int GetNumAll(void) { return m_nNum[m_nType]; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
	 int m_nNum[2];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nType;
};

#endif