//=====================================
//
// テクスチャ処理 [ texture.h ]
// Author: Asuma Nishio
// 
// TODO : ここ変更
// 
//=====================================

#ifndef _TEXTURE_H_ // このマクロ定義がされてなかったら
#define _TEXTURE_H_ // 2重インクルード防止のマクロ定義

//*****************************
// インクルードファイル
//*****************************
#include <string>

//*****************************
// テクスチャ管理クラスを定義
//*****************************
class CTexture
{
public:
	// コンストラクタ・デストラクタ
	CTexture();
	~CTexture();

	// メンバ関数
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	static constexpr int NUM_TEXTURE = 128;	// 最大テクスチャ数

	std::string TEXTURE[NUM_TEXTURE];			// 配列
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTURE];	// テクスチャポインタ
	static int m_nNumAll;							// テクスチャカウント変数
};

#endif