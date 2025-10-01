//=====================================
//
// �e�N�X�`������ [ texture.h ]
// Author: Asuma Nishio
// 
// TODO : �����ύX
// 
//=====================================

#ifndef _TEXTURE_H_ // ���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include <string>

//*****************************
// �e�N�X�`���Ǘ��N���X���`
//*****************************
class CTexture
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTexture();
	~CTexture();

	// �����o�֐�
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	static constexpr int NUM_TEXTURE = 128;	// �ő�e�N�X�`����

	std::string TEXTURE[NUM_TEXTURE];			// �z��
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTURE];	// �e�N�X�`���|�C���^
	static int m_nNumAll;							// �e�N�X�`���J�E���g�ϐ�
};

#endif