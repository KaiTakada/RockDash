//============================
//
// ������ԊǗ�(state_life.cpp)
// Author: Kai Takada
//
//============================
#include "manager.h"
#include "state_life.h"

//===============================
// �}�N����`
//===============================

//=================================
// �R���X�g���N�^
//=================================
CState_Life::CState_Life()
{
	m_nCtrState = 0;
	m_state = STATE_NORMAL;
	m_pAdress = nullptr;

	ZeroMemory(&m_MatDmg, sizeof(D3DXMATERIAL));
}

//=================================
// �f�X�g���N�^
//=================================
CState_Life::~CState_Life()
{

}

//=================================
// �v���C���[�̏���������
//=================================
HRESULT CState_Life::Init(void)
{
	m_MatDmg.MatD3D.Diffuse = D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f);
	m_MatDmg.MatD3D.Ambient = D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f);
	m_MatDmg.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	return S_OK;
}

//=================================
// �v���C���[�̏I������
//=================================
void CState_Life::Uninit(void)
{
	if (m_pAdress != nullptr)
	{
		delete m_pAdress;
		m_pAdress = nullptr;
	}
}

//=================================
// �v���C���[�̍X�V����
//=================================
void CState_Life::Update(void)
{
	if (m_nCtrState == 0)
	{
		switch (m_state)
		{
		case STATE_DAMAGE:
			m_state = STATE_NORMAL;
			break;

		default:
			break;
		}
	}
	else if (m_nCtrState > 0)
	{
		m_nCtrState--;
	}
}

//=================================
// ����
//=================================
CState_Life *CState_Life::Create(void)
{
	//�I�u�W�F�N�g����
	CState_Life *pState= new CState_Life;

	//������
	pState->Init();

	pState->m_pAdress = pState;

	return pState;
}
