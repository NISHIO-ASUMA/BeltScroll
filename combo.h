//***************************************
// 
// コンボ処理 [combo.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _COMBO_H_ // このマクロ定義がされていなかったら
#define _COMBO_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "object.h"
#include "object2D.h"

class CNumber;

//************************
// コンボクラス
//************************
class CCombo :public CObject
{
public:
	CCombo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));	// コンストラクタ
	~CCombo();					// デストラクタ
	static CCombo* Create(D3DXVECTOR3 pos);
	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	int Digit(int nScore);			// 桁を返す
	static void Add(int nScore);	// コンボ加算
	static void Reset(void);		// コンボが途切れた時の設定
	static int GetCombo(void) { return m_nCurrent; }// 現在のコンボ数情報取得
private:
	void Set(void);					// マルチテクスチャの設定
	void SizeUpdate(void);
	static CNumber* m_pNumber[2];	// ナンバーへのポインタ
	static D3DXVECTOR2 m_numberSize;// ナンバーの大きさ
	static int m_nCurrent;					// 現在のコンボ数
	static int m_nTime;						// 継続時間
	static int m_nScore;					// 現在のスコア
	static constexpr int maxNumber = 2;
	static constexpr int maxTime = 1400;	// 最大時間
	static constexpr float offsetX = 35.0f;	// オフセット
	static constexpr float maxHeight = 60.0f;	// 最大の縦の大きさ
	static constexpr float maxWidth = 30.0f;	// 最大の横の大きさ
	static constexpr float deltaHeight = 3.0f;	// 縦の大きさの変化量
	static constexpr float deltaWidth = 1.5f;	// 横の大きさの変化量
	static const D3DXCOLOR COMBO_ON;		// コンボ時の色
	static const D3DXCOLOR COMBO_OFF;		// コンボしてないときの色
};
#endif