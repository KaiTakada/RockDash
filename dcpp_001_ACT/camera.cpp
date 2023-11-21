//============================
//
//�J�����̏���(camera.cpp)
// Author: Kai Takada
//
//============================
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "game.h"
#include "map.h"
#include "cursor.h"
#include "block.h"

//============================
//�}�N����`
//============================
#define CAMERA_SPEED (10.0f)				//�ړ��X�s�[�h
#define CAMERA_ROTSPEED (0.01f)				//��]�X�s�[�h
#define CAMERA_DISTANCE (1000.0f)			//���_�E�����_�̋���
#define CAMERA_INIT_POS_Y (100.0f)			//���_�E�����_��y�����l
#define CAMERA_RADJT (400.0f)				//�����_�̂��炵�l
#define CAMERA_VISDISTANCE (40000.0f)		//�������̒l
#define CAMERA_LIMIT_Z (D3DX_PI * 0.48f)	//z����]�̌��E�l
#define CAMERA_VR_ROT (0.9f)	//���_�ƒ����_�̊p�x
#define CAMERA_Y_STALK (300.0f)	//�v���C���\��y�l�ɍ��킹�ď�������X�^�[�g�l

//============================
// �R���X�g���N�^
//============================
CCamera::CCamera()
{
	m_mtxView = {};
	m_mtxProjection = {};
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = m_posV;
	m_posRDest = m_posR;
	m_posRAdjt = 0.0f;
	m_fDis = 0.0f;
	m_fAngle = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
// �f�X�g���N�^
//============================
CCamera::~CCamera()
{

}

//============================
//�J�����̏���������
//============================
HRESULT CCamera::Init()
{
	m_fDis = CAMERA_DISTANCE;
	m_posV = D3DXVECTOR3(0.0f, CAMERA_INIT_POS_Y, 0.0f - m_fDis);
	m_posR = D3DXVECTOR3(0.0f, CAMERA_INIT_POS_Y * 0.5f, 0.0f);
	m_posVDest = m_posV;
	m_posRDest = m_posR;
	m_posRAdjt = CAMERA_RADJT;
	m_fAngle = D3DX_PI * CAMERA_VR_ROT;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera::Uninit()
{

}

//============================
//�J�����̍X�V����
//============================
void CCamera::Update()
{
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();

	if (pMouse != nullptr)
	{//�J�����������

		if (pMouse->GetChangePos().z >= 10.0f)
		{//�}�E�X���{�^��
			m_fAngle += 0.1f;
		}
		else if (pMouse->GetChangePos().z <= -10.0f)
		{//�}�E�X���{�^��
			m_fAngle -= 0.1f;
		}

		D3DXVECTOR3 mousepos = pMouse->GetPos();

		pDebug->Print("�}�E�X�̈ʒu = X:%f \n", mousepos.x);
		pDebug->Print("�}�E�X�̈ʒu = Y:%f \n", mousepos.y);
		pDebug->Print("�}�E�X�̈ʒu = Z:%f \n", mousepos.z);
		pDebug->Print("�J�����̃A���O���F%f \n", m_fAngle);
	}

	//�v���C���[�ɒǏ]����
	if (CGame::MapFlag())
	{
		EditStalk();
	}
	else
	{
		PlayerStalk();
	}
}

//============================
//�J�����̐ݒ菈��
//============================
void CCamera::SetCamera()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬[�������e]
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,
								CAMERA_VISDISTANCE);

	////�v���W�F�N�V�����}�g���b�N�X�̍쐬[���s���e]-2d���ۂ�
	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//				(float)SCREEN_WIDTH,
	//				(float)SCREEN_HEIGHT,
	//				10.0f,
	//				CAMERA_VISDISTANCE);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,			//���_
						&m_posR,			//�����_
						&m_vecU);		//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===========================
// ��荞�ݏ���
//===========================
void CCamera::CameraStalk()
{
	//����
	float fDiff = 0.0f;
	fDiff = m_rotDest.y - m_rot.y;

	//PI����͂ݏo�Ă����ꍇ�̕␳
	if (fDiff < -D3DX_PI)
	{
		fDiff += D3DX_PI * 2;
	}
	else if (fDiff > D3DX_PI)
	{
		fDiff += -D3DX_PI * 2;
	}
	
	m_rot.y += fDiff * 0.01f;

	//PI����͂ݏo�Ă����ꍇ�̕␳
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
}

//============================
// �G�f�B�b�g�J�[�\���Ǐ]����
//============================
void CCamera::EditStalk(void)
{
	CMap *pMap = CGame::GetMap();

	if (pMap == nullptr)
	{
		return;
	}

	CBlock *pBlock = pMap->GetCursor();

	if (pBlock == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = pBlock->GetPos();
	m_posR.x = pos.x;
	m_posR.z = pos.z;
	m_posR.y = pos.y;

	m_posV.x = pos.x;
	//m_posV.y = pos.y + CAMERA_Y_STALK;
	m_posV.y = pos.y + (sinf(m_fAngle) * m_fDis);
	m_posV.z = pos.z + (cosf(m_fAngle) * m_fDis);
}

//============================
// �v���C���[�Ǐ]����
//============================
void CCamera::PlayerStalk(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPosOld();
	m_posR.x = pos.x;
	m_posR.z = pos.z;
	m_posR.y = pos.y;

	m_posV.x = pos.x;
	//m_posV.y = pos.y + CAMERA_Y_STALK;
	m_posV.y = pos.y + (sinf(m_fAngle) * m_fDis);
	m_posV.z = pos.z + (cosf(m_fAngle) * m_fDis);
}
