//===============================================
//
// チュートリアル管理処理 [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//===============================================

//******************************
// インクルードガード
//******************************
#pragma once

//*********************************
// チュートリアル管理クラスを定義
//*********************************
class CTutorialManager
{
public:

	// デストラクタ
	~CTutorialManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// インスタンス取得
	static CTutorialManager* GetInstance(void);

private:

	// コンストラクタ格納
	CTutorialManager();

};