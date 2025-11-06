//===============================================
// 
// モデルエフェクト処理 [ modeleffect.cpp ]
// Author : Asuma Nishio
// 
//===============================================

//**********************************
// インクルードファイル
//**********************************
#include "modeleffect.h"

//=======================================
// コンストラクタ
//=======================================
CModelEffect::CModelEffect(int nPriority) : CObjectX(nPriority),
m_nLife(NULL),
m_scaleDec(NULL),
m_velocity(VECTOR3_NULL),
m_fRange(NULL)
{
}
//=======================================
// デストラクタ
//=======================================
CModelEffect::~CModelEffect()
{

}
//=======================================
// 生成処理
//=======================================
CModelEffect* CModelEffect::Create(const char* pModelName, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale, int nLife, float scaleDec,float fRange)
{
	// インスタンス生成
	CModelEffect* pEffect = new CModelEffect;
	if (pEffect == nullptr) return nullptr;

	// オブジェクト設定
	pEffect->SetFilePass(pModelName);
	pEffect->SetPos(pos);
	pEffect->SetRot(rot);
	pEffect->SetScale(scale);
	pEffect->SetScaleDec(scaleDec);
	pEffect->SetLife(nLife);
	pEffect->m_fRange = fRange;

	if (FAILED(pEffect->Init()))
	return nullptr;

	return pEffect;
}
//=======================================
// 初期化処理
//=======================================
HRESULT CModelEffect::Init(void)
{
	CObjectX::Init();

	return S_OK;
}
//=======================================
// 終了処理
//=======================================
void CModelEffect::Uninit(void)
{
	CObjectX::Uninit();
}
//=======================================
// 更新処理
//=======================================
void CModelEffect::Update(void)
{
	D3DXVECTOR3 Pos = GetPos();		// 位置の取得
	D3DXVECTOR3 Rot = GetRot();		// 向きの取得
	D3DXVECTOR3 Size = GetSize();	// サイズの取得

	if (m_nLife <= 0 || Size.x <= 0.0f || Size.y <= 0.0f || Size.z <= 0.0f)
	{
		// 終了処理
		Uninit();
		return;
	}

	// ベクトル
	D3DXVECTOR3 dir = VECTOR3_NULL;

	// ランダム方向に少しばらつかせる
	dir.x += ((float)(rand() % 190 - 80)) * 0.04f; // X方向ランダム
	dir.y += 0.0f;
	dir.z += ((float)(rand() % 190 - 80)) * 0.04f; // Z方向ランダム

	// 正規化
	D3DXVec3Normalize(&dir, &dir);

	// スピードを範囲に比例させる
	float fSpeed = ((float)(rand() % 50) / 10.0f) + (m_fRange * 0.3f);

	// 角度回転
	Rot.x += 0.03f;
	Rot.y += 0.03f;

	// 角度の正規化
	if (Rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		Rot.y -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (Rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		Rot.y += D3DX_PI * 2.0f;
	}

	// 角度の正規化
	if (Rot.x > D3DX_PI)
	{// D3DX_PIより大きくなったら
		Rot.x -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (Rot.x < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		Rot.x += D3DX_PI * 2.0f;
	}

	// 角度の正規化
	if (Rot.z > D3DX_PI)
	{// D3DX_PIより大きくなったら
		Rot.z -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (Rot.z < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		Rot.z += D3DX_PI * 2.0f;
	}

	// 移動ベクトル
	D3DXVECTOR3 Move = dir * fSpeed;
	Pos += Move;

	// 寿命を減らす
	m_nLife--;

	// サイズの減衰
	Size.x -= m_scaleDec;
	Size.y -= m_scaleDec;
	Size.z -= m_scaleDec;

	SetPos(Pos);
	SetRot(Rot);
	SetScale(Size);

	// 親クラスの更新
	CObjectX::Update();
}