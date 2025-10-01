//=====================================
//
// �e�N�X�`������ [ texture.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "texture.h"
#include "manager.h"

//**********************
// �ÓI�����o�ϐ�
//**********************
int CTexture::m_nNumAll = NULL;	// �����Ǘ�

//===============================
// �R���X�g���N�^
//===============================
CTexture::CTexture()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
}
//===============================
// �f�X�g���N�^
//===============================
CTexture::~CTexture()
{
	// ����
}
//===============================
// �e�N�X�`���ǂݍ���
//===============================
HRESULT CTexture::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���ׂẴe�N�X�`������
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// �����񂪂�������
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

	// ���ʂ�Ԃ�
	return S_OK;

}
//===============================
// �e�N�X�`���j��
//===============================
void CTexture::UnLoad(void)
{
	// ���ׂẴe�N�X�`���̔j��
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// �z��̘A���N���A
		TEXTURE[nCnt].clear();

		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}
//===============================
// �e�N�X�`���ԍ���o�^����
//===============================
int CTexture::Register(const char* pFileName)
{
	// �e�N�X�`������������
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		if (!TEXTURE[nCnt].empty() && TEXTURE[nCnt] == pFileName)
		{
			return nCnt; // �C���f�b�N�X��Ԃ�
		}
	}

	// ����������V�K�쐬
	if (m_nNumAll < NUM_TEXTURE)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���쎞
		if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice, pFileName, &m_apTexture[m_nNumAll])))
		{
			// �t�@�C������o�^
			TEXTURE[m_nNumAll] = pFileName;

			// ������Ԃ�
			return m_nNumAll++;
		}
	}

	// �e�N�X�`�����Ȃ��ꍇ
	return -1;
}
//===============================
// �e�N�X�`���ԍ��擾
//===============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	// ��O����
	if (nIdx < 0 || nIdx >= NUM_TEXTURE) return nullptr;

	// �e�N�X�`���ԍ����擾
	return m_apTexture[nIdx];
}