//============================
//
//���C�g(light.cpp)
// Author: Kai Takada
//
//============================
#include "manager.h"
#include "light.h"

//============================
// �R���X�g���N�^
//============================
CLight::CLight()
{

}

//============================
// �f�X�g���N�^
//============================
CLight::~CLight()
{

}

//============================
//���C�g�̏���������
//============================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;		//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCntLight)
		{//���C�g�̊g�U�Z�ƕ�����ݒ�
		case 0:
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			break;

		case 1:
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			break;

		case 2:
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			break;

		default:
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K������(1.0f�ɂ���)
		m_light[nCntLight].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//============================
//���C�g�̏I������
//============================
void CLight::Uninit(void)
{

}

//============================
//���C�g�̍X�V����
//============================
void CLight::Update(void)
{

}
