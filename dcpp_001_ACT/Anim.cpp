//===============================================
//
// �A�j���[�V����(Anim.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "Anim.h"
#include "texture.h"

//============================
// �}�N����`
//============================

//============================
// �O���錾
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^
//============================
CAnim::CAnim()
{
	m_nCtrAnim = 0;							//�A�j���[�V�����J�E���^�[
	m_nPtnAnimX = 0;						//�A�j���[�V�����p�^�[��x No.
	m_nPtnAnimY = 0;						//�A�j���[�V�����p�^�[��y No.
	m_nNumPtnAnimX = 0;						//�A�j���[�V�����p�^�[����x
	m_nNumPtnAnimY = 0;						//�A�j���[�V�����p�^�[����y
	m_nFrame = 0;		//�X�V�p�x�t���[��
	m_nLoop = 0;		//���[�v��(-1�Ŗ���)

	for (int nCntTex = 0; nCntTex < MAX_VTX; nCntTex++)
	{
		m_aTexpos[nCntTex] = {};
	}
}

//============================
// �f�X�g���N�^
//============================
CAnim::~CAnim()
{

}

//============================
// ������
//============================
HRESULT CAnim::Init(void)
{
	m_nCtrAnim = 0;
	m_nPtnAnimX = 0;
	m_nPtnAnimY = 0;
	m_nNumPtnAnimX = 2;
	m_nNumPtnAnimY = 5;
	m_nFrame = 10;
	m_nLoop = 0;
	
	for (int nCntTex = 0; nCntTex < MAX_VTX; nCntTex++)
	{
		m_aTexpos[nCntTex] = D3DXVECTOR2(0.0f, 0.0f);
	}

	return S_OK;
}

//============================
// �I��
//============================
void CAnim::Uninit(void)
{

}

//============================
// �X�V
//============================
void CAnim::Update(void)
{
	float fTexX = 1.0f / m_nNumPtnAnimX;
	float fTexY = 1.0f / m_nNumPtnAnimY;

	m_nCtrAnim++;							//�J�E���^�[�����Z

	if ((m_nCtrAnim % m_nFrame) == 0)
	{
		m_nCtrAnim = 0;					//�J�E���^�[�������l�ɖ߂�
		m_nPtnAnimX++;						//�J�E���^�[���X�V����

		if (m_nPtnAnimX > m_nNumPtnAnimX * m_nNumPtnAnimY - 1)
		{
			m_nPtnAnimY++;		//��i�ڂƓ�i�ڂ̐؂�ւ�	

			if (m_nPtnAnimY >= m_nNumPtnAnimY)
			{//1���[�v
				m_nPtnAnimY = 0;

				m_nLoop--;
			}

			m_nPtnAnimX = 0;				//�J�E���^�[�������l�ɖ߂�
		}
	}

	float fTexposX = m_nPtnAnimX * fTexX;
	float fTexposY = m_nPtnAnimY * fTexY;

	//�e�N�X�`�����W�̐ݒ�
	m_aTexpos[0] = D3DXVECTOR2(fTexposX, fTexposY);				//(x,y)
	m_aTexpos[1] = D3DXVECTOR2(fTexposX + fTexX, fTexposY);
	m_aTexpos[2] = D3DXVECTOR2(fTexposX, fTexposY + fTexY);
	m_aTexpos[3] = D3DXVECTOR2(fTexposX + fTexX, fTexposY + fTexY);
}

//============================
// �e�N�X�`�����W�ݒ�
//============================
void CAnim::SetTexpos(const D3DXVECTOR2 * pTexpos)
{
	for (int nCntTex = 0; nCntTex < MAX_VTX; nCntTex++)
	{
		m_aTexpos[nCntTex] = pTexpos[nCntTex];
	}
}
