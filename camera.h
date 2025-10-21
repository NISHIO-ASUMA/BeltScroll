//=====================================
//
// �J�������� [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _CAMERA_H_ // ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �O���錾
//**********************
class CInputMouse;
class CInputKeyboard;

//**********************
// �J�����N���X���`
//**********************
class CCamera
{
public:
	//**********************
	// �J�������[�h�񋓌^
	//**********************
	enum MODE
	{
		MODE_NONE,
		MODE_PLAYER,
		MODE_LOCKON,
		MODE_MOUSE,
		MODE_SHAKE,
		MODE_EVENT,
		MODE_ANIM,
		MODE_MAIN,
		MODE_SUB,
		MODE_MAX

	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CCamera();
	~CCamera();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void MouseView(CInputMouse* pMouse, CInputKeyboard* pInput);
	void WheelMouse(int nDelta);
	void PlayerFllow(void);
	bool PlayerCollisionScreen(D3DXVECTOR3 playerPos);
	void Tameshi(void);

	// �Z�b�^�[
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }

	// �Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXVECTOR3 GetPos(void) { return m_pCamera.posV; }
	D3DXVECTOR3 GetPosR(void) { return m_pCamera.posR; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }
	float GetDistance(void) { return m_pCamera.fDistance; }

private:

	//*************************
	// �J�����\���̂��`
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
		D3DXVECTOR3 posV, posR;		// ���_,�����_���W
		D3DXVECTOR3 rot;			// �p�x
		D3DXVECTOR3 vecU;			// �@���x�N�g��
		D3DXVECTOR3 posRDest;		// �ړI���W
		float fDistance;			// �J�����̋���
		int nMode;					// �J�����̃��[�h
		int nUseKey;				// �A�j���[�V�����g�p���ɓǂݎ��L�[��
		int nCntAnim;				// �J�E���g
	};

	Camera m_pCamera;		// �J�����\���̕ϐ�
	D3DXVECTOR3 m_Zoom;		// �Y�[��
};

#endif