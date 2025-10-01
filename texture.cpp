//=====================================
//
// テクスチャ処理 [ texture.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "texture.h"
#include "manager.h"

//**********************
// 静的メンバ変数
//**********************
int CTexture::m_nNumAll = NULL;	// 総数管理

//===============================
// コンストラクタ
//===============================
CTexture::CTexture()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
}
//===============================
// デストラクタ
//===============================
CTexture::~CTexture()
{
	// 無し
}
//===============================
// テクスチャ読み込み
//===============================
HRESULT CTexture::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// すべてのテクスチャ分回す
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// 文字列があったら
		if (!TEXTURE[nCnt].empty())
		{
			HRESULT hr = D3DXCreateTextureFromFile(
				pDevice,
				TEXTURE[nCnt].c_str(),
				&m_apTexture[nCnt]);

			if (FAILED(hr))
			{
				m_apTexture[nCnt] = nullptr;
			}
		}
		else
		{
			m_apTexture[nCnt] = nullptr;
		}
	}

	// 結果を返す
	return S_OK;

}
//===============================
// テクスチャ破棄
//===============================
void CTexture::UnLoad(void)
{
	// すべてのテクスチャの破棄
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// 配列の連結クリア
		TEXTURE[nCnt].clear();

		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}
//===============================
// テクスチャ番号を登録する
//===============================
int CTexture::Register(const char* pFileName)
{
	// テクスチャがあったら
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		if (!TEXTURE[nCnt].empty() && TEXTURE[nCnt] == pFileName)
		{
			return nCnt; // インデックスを返す
		}
	}

	// 無かったら新規作成
	if (m_nNumAll < NUM_TEXTURE)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// 制作時
		if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, pFileName, &m_apTexture[m_nNumAll])))
		{
			// ファイル名を登録
			TEXTURE[m_nNumAll] = pFileName;

			// 総数を返す
			return m_nNumAll++;
		}
	}

	// テクスチャがない場合
	return -1;
}
//===============================
// テクスチャ番号取得
//===============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	// 例外処理
	if (nIdx < 0 || nIdx >= NUM_TEXTURE) return nullptr;

	// テクスチャ番号を取得
	return m_apTexture[nIdx];
}