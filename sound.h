//=====================================
//
// サウンド処理 [ sound.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SOUND_H_ // このマクロ定義がされてなかったら
#define _SOUND_H_ // 2重インクルード防止のマクロ定義

//******************************
// サウンドクラスを定義
//******************************
class CSound
{
public:
	//***************************
	// サウンドの種類列挙型
	//***************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_TITLE_BGM,		// タイトルBGM
		SOUND_LABEL_GAMEBGM,		// ゲームBGM
		SOUND_LABEL_RESULTBGM,		// リザルトBGM
		SOUND_LABEL_RESULTLOSEBGM,	// 負けリザルトBGM
		SOUND_LABEL_TUTORIALBGM,	// チュートリアルBGM
		SOUND_LABEL_RANKINGBGM,		// ランキングBGM
		SOUND_LABEL_CLICKSE,		// 決定音
		SOUND_LABEL_WIND,			// 風っぽい音
		SOUND_LABEL_SELECTSE,		// 選択音
		SOUND_LABEL_DEATHSE,		// 敵の吸い込まれる音
		SOUND_LABEL_BOUNSSE,		// ボーナス音
		SOUND_LABEL_MAX
	};

	// コンストラクタ・デストラクタ
	CSound();
	~CSound();

	// メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	//*****************************
	// サウンド情報の構造体定義
	//*****************************
	struct SOUNDINFO
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	};

	//******************************
	// サウンドの情報列挙型宣言
	//******************************
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/Title001.wav", -1},		 // タイトルBGM
		{"data/BGM/game_bgm.wav",-1},		 // ゲームBGM
		{"data/BGM/Result.wav",-1},			 // リザルトBGM
		{"data/BGM/result_lose.wav",-1},	 // 負けリザルトBGM
		{"data/BGM/tutorialbgm.wav",-1},	 // チュートリアルBGM
		{"data/BGM/ranking_bgm.wav",-1},	 // ランキングBGM
		{"data/SE/ClickEnter.wav",0},		 // 決定音
		{"data/SE/Change.wav",0},			 // ブロワー変更音
		{"data/SE/select.wav",0},			 // 選択音
		{"data/SE/death_SE.wav",0},			 // 敵が吸い込まれる音
		{"data/SE/Charge02.wav",0},			 // ボーナス加算音
	};

	IXAudio2* m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	int m_SoundCount;										// サウンドのカウント
	int m_SoundInterval;									// インターバルカウント

};

#endif