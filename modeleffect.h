//===============================================
// 
// モデルエフェクト処理 [ modeleffect.h ]
// Author : Asuma Nishio
// 
//===============================================

//**********************************
// インクルードガード
//**********************************
#pragma once

//**********************************
// インクルードファイル
//**********************************
#include "objectX.h"

//**********************************
// モデルエフェクト用クラスを定義
//**********************************
class CModelEffect : public CObjectX
{
public:

	CModelEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CModelEffect();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetScaleDec(float fDec) { m_scaleDec = fDec; }
	void SetLife(int nLife) { m_nLife = nLife; }

	static CModelEffect* Create(
		const char * pModelName,const D3DXVECTOR3 pos,const D3DXVECTOR3 rot,const D3DXVECTOR3 scale,
		int nLife, float scaleDec,float fRange);

private:
	int m_nLife;			// 寿命
	float m_scaleDec;		// サイズの減少
	float m_fRange;			// 拡散する半径
	D3DXVECTOR3 m_velocity; // 速度
	D3DXMATERIAL m_Mat;	// カラーマテリアル
};