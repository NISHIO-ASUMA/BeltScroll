//=====================================
//
// X�t�@�C������ [ objectX.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _OBJECTX_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECTX_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//******************************
// �I�u�W�F�N�gX�N���X���`
//******************************
class CObjectX : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CObjectX(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CObjectX();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void); 

	// �Z�b�^�[
	void SetFilePass(const char* pFilePass) { m_pFileName = pFilePass; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetUseQuat(bool isFlags) { m_isUseQaut = isFlags; }
	void SetMtxWorld(D3DXMATRIX mtxworld) { m_mtxWorld = mtxworld; }
	void SetParent(CObjectX* pParent) { m_pParent = pParent; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	D3DXVECTOR3 GetRot(void) { return m_rot; };
	D3DXVECTOR3 GetScale(void) { return m_Scale; }
	D3DXVECTOR3 GetSize(void) { return m_fsize; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	CObjectX*GetParent(void) { return m_pParent; }


	const char* GetFileName()const { return m_pFileName; }

	// �ÓI�����o�֐�
	static CObjectX* Create(const char* pFileName,D3DXVECTOR3 pos);

private:
	D3DXMATRIX m_mtxWorld; // ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;	   // ���b�V�����
	LPD3DXBUFFER m_pBuffMat; // �}�e���A�����
	DWORD m_dwNumMat;		// �}�e���A����
	CObjectX* m_pParent;	// �e

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_Scale;	// �g�嗦
	D3DXVECTOR3 m_fsize;	// �T�C�Y
	D3DXVECTOR3 m_Vtxmin;
	D3DXVECTOR3 m_Vtxmax;

	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	int* m_pTexture;		// �e�N�X�`���|�C���^

	const char* m_pFileName; // �t�@�C����

	bool m_isUseQaut;		 // �N�H�[�^�j�I�����ǂ���
};

#endif