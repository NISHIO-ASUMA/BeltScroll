//**********************************
//
// コンボ処理 [combo.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "combo.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "number.h"

//**********************
// 静的メンバ変数初期化
//**********************
CNumber* CCombo::m_pNumber[2] = {};
int CCombo::m_nCurrent = 0;
int CCombo::m_nTime = 0;
int CCombo::m_nScore = 0;
D3DXVECTOR2 CCombo::m_numberSize = D3DXVECTOR2(0.0f, 0.0f);
const D3DXCOLOR CCombo::COMBO_ON = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR CCombo::COMBO_OFF = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

//*****************
// コンストラクタ
//*****************
CCombo::CCombo(int nPriority) :CObject(nPriority)
{
}

//*****************
// デストラクタ
//*****************
CCombo::~CCombo()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CCombo::Init(void)
{
	m_nCurrent = 0;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CCombo::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumber[nCnt]->Uninit();
		delete m_pNumber[nCnt];
		m_pNumber[nCnt] = nullptr;
	}
	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CCombo::Update(void)
{
	// コンボ終了時のリセット
	Reset();

	// コンボ数の表示
	Set();

	SizeUpdate();

	// タイマーを減らす
	m_nTime--;
}

//*****************
// 描画処理
//*****************
void CCombo::Draw(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//******************
// インスタンス生成
//******************
CCombo* CCombo::Create(D3DXVECTOR3 pos)
{
	// パーティクルのポインタを宣言
	CCombo* pCombo = new CCombo;

	// nullだったら
	if (pCombo == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pCombo->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		pCombo->m_pNumber[nCnt] = new CNumber;
	}
	m_pNumber[0]->Init(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f), 0.0f, 0.0f);
	m_pNumber[1]->Init(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f), 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumber[nCnt]->SetCol(COMBO_OFF);
		m_pNumber[nCnt]->SetTexture("score001.png");
	}

	// ポインタを返す
	return pCombo;
}

//*****************
// 位置設定
//*****************
void CCombo::SetPos(D3DXVECTOR3 pos)
{
	m_pNumber[0]->SetPos(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f));
	m_pNumber[1]->SetPos(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f));
}

//*****************
// 桁数を返す
//*****************
int CCombo::Digit(int nScore)
{
	int nNum = nScore;
	int nKeepNum = 0;

	// 割り切れなくなるまで繰り返す
	while (nNum != 0)
	{
		nNum /= 10;// 10で割る
		nKeepNum++;// 桁数を加算
	}
	if (nScore == 0)
	{
		nKeepNum = 1;// 1桁目が０の時
	}

	return nKeepNum;
}

//*************
// コンボ加算
//*************
void CCombo::Add(int nScore)
{
	// コンボ数加算
	m_nCurrent++;
	m_nTime = maxTime;
	m_nScore += nScore;
	m_numberSize = D3DXVECTOR2(0.0f, 0.0f);
}

//****************
// コンボ数の表示
//****************
void CCombo::Set(void)
{
	int nData[2], nTime;

	// 初期化
	nData[0] = 10;
	nData[1] = 1;
	nTime = m_nTime / (maxTime / 100);

	// ナンバーに値を設定
	for (int nCntD = 0; nCntD < 2; nCntD++)
	{
		// 計算して値を1桁ずつ設定
		m_pNumber[nCntD]->SetDigit((m_nCurrent % nData[0]) / nData[1]);
		nData[0] *= 10;
		nData[1] *= 10;
		m_pNumber[nCntD]->SetCol(COMBO_OFF);
	}

	// ナンバー桁数分描画
	if (m_nCurrent >= 1)
	{
		for (int nCntD = 0; nCntD < Digit(m_nCurrent); nCntD++)
		{
			m_pNumber[nCntD]->SetCol(COMBO_ON);
		}
	}
}

//*************
// コンボ終了
//*************
void CCombo::Reset(void)
{
	//// ゲーム状態の取得
	//CGame::STATE state = CGame::GetState();
	//if (m_nTime <= 0 || state == CGame::STATE_END)
	//{// 時間経過orゲーム終了したら

	//	// コンボ数に応じてスコア加算
	//	int nFinishCombo = m_nCurrent;
	//	CScore::Add(m_nScore * nFinishCombo);

	//	// 初期化
	//	m_nCurrent = 0;
	//	m_nTime = 0;
	//	m_nScore = 0;
	//}

}

//******************
// 数字の大きさ更新
//******************
void CCombo::SizeUpdate(void)
{

	m_numberSize.x += deltaHeight;
	m_numberSize.y += deltaWidth;

	// 最大の大きさで止める
	if (m_numberSize.x >= maxHeight)
	{
		m_numberSize.x = maxHeight;
	}
	if (m_numberSize.y >= maxWidth)
	{
		m_numberSize.y = maxWidth;
	}
	// 反映
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumber[nCnt]->SetSize(m_numberSize.x, m_numberSize.y);
	}
}