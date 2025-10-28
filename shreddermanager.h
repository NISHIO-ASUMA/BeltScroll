//======================================================
//
// �V�����b�_�[�}�l�[�W���[���� [ shreddermanager.h ]
// Author: Asuma Nishio
//
//======================================================

#ifndef _SHREDDERMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _SHREDDERMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �O���錾
//**************************
class CShredder;

//******************************
// �V�����b�_�[�Ǘ��N���X���`
//******************************
class CShredderManager
{
public:
	typedef enum
	{
		TYPE_RED = 0,
		TYPE_GREEN,
	}TYPE;

	// �R���X�g���N�^�E�f�X�g���N�^
	CShredderManager();
	~CShredderManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Swap(void);

	// �Q�b�^�[
	CShredder* GetShredder(const int nIdx) { return m_pShredder[nIdx]; }

private:
	CShredder* m_pShredder[2];	// �|�C���^
	int m_nSwapCnt;				// ����ւ���J�E���g
	bool m_bRedFlont;			// �Ԃ��ق�����O�ɂ��邩
	static constexpr int SWAPCOUNT = 300;
	static constexpr float FIXED_Z00 = -250.0f;
	static constexpr float FIXED_Z01 = 250.0f;
};

#endif