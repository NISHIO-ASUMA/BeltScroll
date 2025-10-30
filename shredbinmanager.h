//======================================================
//
// �V�����b�h�r���}�l�[�W���[���� [ shredbinmanager.h ]
// Author: Soichiro Sasaki
//
//======================================================

#ifndef _SHREDBINMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _SHREDBINMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �V�����b�_�[�Ǘ��N���X���`
//******************************
class CShredbinManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CShredbinManager();
	~CShredbinManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �Q�b�^�[
	static int GetNumAll(void) { return m_nNum; }

private:
	static int m_nNum;
	D3DXVECTOR3 m_pos;
};

#endif