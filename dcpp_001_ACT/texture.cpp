//===============================================
//
// �e�N�X�`��(texture.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "texture.h"
#include "manager.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================
int CTexture::m_nNumAll = 0;				//���ʃe�N�X�`���o�b�t�@

//============================
// �e�N�X�`���p�X
//============================
const char *c_apTexFilepass[] =
{
	"data\\TEXTURE\\null.jpg"
};

//==========================================
//============= 2D�A�j���[�V���� =============
//============================
// �R���X�g���N�^
//============================
CTexture::CTexture()
{
	for (int nCntCons = 0; nCntCons < MAX_TEXTURE; nCntCons++)
	{
		//�e�N�X�`���j��
		if (m_apTexture[nCntCons] != nullptr)
		{
			m_apTexture[nCntCons] = nullptr;
		}
		//�e�N�X�`�����j��
		if (apFilename[nCntCons] != nullptr)
		{
			apFilename[nCntCons] = nullptr;
		}
	}
}

//============================
// �f�X�g���N�^
//============================
CTexture::~CTexture()
{
	for (int nCntDes = 0; nCntDes < MAX_TEXTURE; nCntDes++)
	{
		//�e�N�X�`���j��
		if (m_apTexture[nCntDes] != nullptr)
		{
			m_apTexture[nCntDes] = nullptr;
		}
		//�e�N�X�`�����j��
		if (apFilename[nCntDes] != nullptr)
		{
			apFilename[nCntDes] = nullptr;
		}
	}
}

//============================
// ���L�e�N�X�`���擾
//============================
HRESULT CTexture::Load(void)
{
	for (int nCntFile = 0; nCntFile < sizeof(c_apTexFilepass) / sizeof(c_apTexFilepass[0]); nCntFile++)
	{
		Regist(c_apTexFilepass[nCntFile]);
	}

	return S_OK;
}

//============================
// ���L�e�N�X�`���j��
//============================
void CTexture::Unload(void)
{
	for (int nCntUnload = 0; nCntUnload < MAX_TEXTURE; nCntUnload++)
	{
		//�e�N�X�`���j��
		if (m_apTexture[nCntUnload] != nullptr)
		{
			m_apTexture[nCntUnload]->Release();
			m_apTexture[nCntUnload] = nullptr;
		}

		if (apFilename[nCntUnload] != nullptr)
		{
			apFilename[nCntUnload] = nullptr;
		}
	}
}

//============================
// �e�N�X�`���ǉ��Ǎ�
//============================
int CTexture::Regist(const char *pFilename)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntReg = 0; nCntReg < MAX_TEXTURE; nCntReg++)
	{
		if (m_apTexture[nCntReg] != nullptr)
		{//��񂪓����Ă���
		
			if (strcmp(apFilename[nCntReg], pFilename) == 0)
			{//���łɓǂݍ���ł����
			
				return nCntReg;
			}
		}
		else if (m_apTexture[nCntReg] == nullptr)
		{//NULL�`�F�b�N

		 //�e�N�X�`���̓ǂݍ���[0]
			if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice,
				pFilename,			//�e�N�X�`���̃t�@�C����
				&m_apTexture[nCntReg])))
			{//���������ꍇ
				//strcpy(apFilename[nCntReg], pFilename);
				apFilename[nCntReg] = (char*)pFilename;
				m_nNumAll++;
				return nCntReg;
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

//============================
// �ԍ��ɍ������e�N�X�`����n��
//============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx < 0 || nIdx > MAX_TEXTURE)
	{
		return nullptr;
	}
	else
	{
		return m_apTexture[nIdx];
	}
}
