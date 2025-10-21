//====================================
//
// �J�������� [ camera.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "object.h"
#include "template.h"
#include "player.h"
#include "gamemanager.h"
#include "game.h"

//**********************
// �萔�錾
//**********************
namespace CAMERAINFO
{
	constexpr float MAX_VIEWUP = 3.0f;			// �J�����̊p�x�����l
	constexpr float MAX_VIEWDOWN = 0.1f;		// �J�����̊p�x�����l
	constexpr float NorRot = D3DX_PI * 2.0f;	// ���K���l
	constexpr float CAMERABACKPOS = 450.0f;		// ����J����
	constexpr float SHAKEVALUE = 12.0f;			// �U���̒l
	constexpr float DIGITVALUE = 1.5f;		// ����l
	constexpr int RANDOMBASE = 2;			// �����_����l
}

//=================================
// �R���X�g���N�^
//=================================
CCamera::CCamera()
{
	// �l�̃N���A
	m_pCamera.mtxprojection = {};
	m_pCamera.mtxView = {};
	m_pCamera.posR = VECTOR3_NULL;
	m_pCamera.posV = VECTOR3_NULL;
	m_pCamera.rot = VECTOR3_NULL;
	m_pCamera.vecU = VECTOR3_NULL;
	m_pCamera.posRDest = VECTOR3_NULL;
	m_pCamera.fDistance = NULL;
	m_pCamera.nMode = MODE_NONE;
	m_pCamera.nUseKey = NULL;
	m_pCamera.nCntAnim = NULL;
	m_Zoom = VECTOR3_NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CCamera::~CCamera()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CCamera::Init(void)
{
	// �����l��ݒ肷��
	m_pCamera.posV = D3DXVECTOR3(0.0f, 650.0f, -700.0f);		// �J�����̈ʒu
	m_pCamera.posR = VECTOR3_NULL;								// �J�����̌��Ă���ʒu
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	m_pCamera.rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);	// �p�x

	// �������v�Z
	float fRotx = m_pCamera.posV.x - m_pCamera.posR.x;
	float fRoty = m_pCamera.posV.y - m_pCamera.posR.y;
	float fRotz = m_pCamera.posV.z - m_pCamera.posR.z;

	// ���_���璍���_�܂ł̋���
	m_pCamera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));

	// ���[�h�̏�����
	m_pCamera.nMode = MODE_NONE;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CCamera::Uninit(void)
{
	// ����
}
//=================================
// �X�V����
//=================================
void CCamera::Update(void)
{
	// ���͏����擾
	CInputMouse* pMouse = CManager::GetMouse();
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

#ifdef _DEBUG

	// �}�E�X�X�V
	MouseView(pMouse, pInput);

	// �Ǐ]
	Tameshi();

	//PlayerFllow();
#else

	// �Ǐ]�J����
	PlayerFllow();

#endif // _DEBUG

	// �p�x�̐��K��
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_pCamera.rot.y -= CAMERAINFO::NorRot;
	}

	// �p�x�̐��K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
}
//=================================
// �J�������Z�b�g
//=================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxView);

	// �Z�o���ꂽ���W����ɂ���
	D3DXVECTOR3 posVForView = m_pCamera.posV;

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&posVForView,
		&m_pCamera.posR,
		&m_pCamera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxprojection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_pCamera.mtxprojection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera.mtxprojection);
}
//======================================
// �}�E�X����̎��_�ړ�
//======================================
void CCamera::MouseView(CInputMouse* pMouse, CInputKeyboard* pInput)
{
	// ���N���b�N
	if (pMouse->GetPress(CInputMouse::MOUSE_LEFT) && pInput->GetPress(DIK_LSHIFT))
	{
		// �}�E�X�̈ړ��ʎ擾
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		// ���݂̊p�x���v�Z
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�����̎��_�̏��
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// �E�N���b�N
	else if (pMouse->GetPress(CInputMouse::MOUSE_RIGHT) && pInput->GetPress(DIK_LSHIFT))
	{
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�������W���X�V
		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.y = m_pCamera.posV.y + cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;

	}

	// ���K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CAMERAINFO::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CAMERAINFO::NorRot;
	}
}
//==============================
// �}�E�X�z�C�[������
//==============================
void CCamera::WheelMouse(int nDelta)
{
	// ���[�J���ϐ�
	m_Zoom = m_pCamera.posV - m_pCamera.posR;
	D3DXVec3Normalize(&m_Zoom, &m_Zoom);

	if (CManager::GetInputKeyboard()->GetPress(DIK_LSHIFT))
	{
		if (nDelta > 0)
		{// �}�E�X�̒l����
			m_pCamera.fDistance -= 10.0f;
		}
		else if (nDelta < 0)
		{// �}�E�X�̒l����
			m_pCamera.fDistance += 10.0f;
		}

		if (m_pCamera.fDistance <= 250.0f)
		{// 250.0f�ȉ��Ȃ�
			m_pCamera.fDistance = 250.0f;
		}

		// �J�����̎��_�̏��
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
}
//==============================
// �Ǐ]�J��������
//==============================
void CCamera::PlayerFllow(void)
{
#if 1
	// ���݂̃��[�h�擾
	CScene::MODE nMode = CManager::GetScene();

	if (nMode != CScene::MODE_GAME)
	{
		return;
	}

	// �v���C���[�擾
	CPlayer* pPlayer = CGame::GetGameManager()->GetPlayer();

	// nullptr�`�F�b�N
	if (pPlayer == nullptr)
	{
		// �����ŏ�����Ԃ�
		return;
	}
	if (PlayerCollisionScreen(pPlayer->GetPos()))
	{

	}

	// �Ǐ]�J�����p�ɐݒ�
	m_pCamera.posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.y = pPlayer->GetPos().y + cosf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRotDest().y) * 1.0f;

	m_pCamera.posR.x += ((m_pCamera.posRDest.x - m_pCamera.posR.x) * 0.3f);
	m_pCamera.posR.y += ((m_pCamera.posRDest.y - m_pCamera.posR.y) * 0.3f);
	m_pCamera.posR.z += ((m_pCamera.posRDest.z - m_pCamera.posR.z) * 0.3f);

	// �J�����̎��_�̏��
	m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
	m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
	m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;

#endif
}

//**********************************************************
// �v���C���[����ʒ[�ɍs�����Ƃ��ɃJ�����𓮂������߂̔���
//**********************************************************
bool CCamera::PlayerCollisionScreen(D3DXVECTOR3 playerPos)
{

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetRenderer();
	pDevice = renderer->GetDevice();

	D3DXMATRIX matProj, matView, matWorld;
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 pos;
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	D3DXVec3Project(&pos, &playerPos, &viewport, &matProj, &matView, &matWorld);

	if (pos.x > SCREEN_WIDTH * 0.75f)
	{
		return true;
	}

	return false;

}

//**********************************************************
// �����ł�
//**********************************************************
void CCamera::Tameshi(void)
{
#if 1
	// ���݂̃��[�h�擾
	CScene::MODE nMode = CManager::GetScene();

	if (nMode != CScene::MODE_GAME)
	{
		return;
	}

	// �v���C���[�擾
	CPlayer* pPlayer = CGame::GetGameManager()->GetPlayer();

	// nullptr�`�F�b�N
	if (pPlayer == nullptr)
	{
		// �����ŏ�����Ԃ�
		return;
	}
	if (PlayerCollisionScreen(pPlayer->GetPos())&& pPlayer->GetPos().x > pPlayer->GetOldPos().x)
	{
		// �Ǐ]�J�����p�ɐݒ�
		m_pCamera.posRDest.x += pPlayer->GetPos().x - pPlayer->GetOldPos().x;

		m_pCamera.posR.x += ((m_pCamera.posRDest.x - m_pCamera.posR.x) * 0.3f);
		m_pCamera.posR.y += ((m_pCamera.posRDest.y - m_pCamera.posR.y) * 0.3f);
		m_pCamera.posR.z += ((m_pCamera.posRDest.z - m_pCamera.posR.z) * 0.3f);

		// �J�����̎��_�̏��
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}


#endif

}