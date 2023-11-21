//===============================================
//
// �}���`�w�i(multibg.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "multibg.h"
#include "bg.h"
#include "object2D.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^(�f�t�H)
//============================
CMultiBg::CMultiBg()
{
	for (int nCntCrt = 0; nCntCrt < MAX_MULTIBG; nCntCrt++)
	{
		if (m_apObject[nCntCrt] != nullptr)
		{
			m_apObject[nCntCrt] = nullptr;
		}
	}
}

//============================
// �f�X�g���N�^
//============================
CMultiBg::~CMultiBg()
{

}
//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CMultiBg::Init(void)
{
	for (int nCntCrt = 0; nCntCrt < MAX_MULTIBG; nCntCrt++)
	{
		if (m_apObject[nCntCrt] == nullptr)
		{
			m_apObject[nCntCrt] = CObject2D::Create();		//���g����

			if (m_apObject[nCntCrt] != nullptr)
			{
				m_apObject[nCntCrt]->Init();
			}

			break;
		}
	}

	return S_OK;
}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CMultiBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR2 move, const D3DXVECTOR3 size, int nNum)
{
	int nNumTex = 0;

	if (nNum > MAX_MULTIBG)
	{
		return E_FAIL;
	}

	for (int nCntCrt = 0; nCntCrt < nNum; nCntCrt++)
	{
		for (int nCntAll = 0; nCntAll < MAX_MULTIBG; nCntAll++)
		{
			if (m_apObject[nCntAll] == nullptr)
			{
				m_apObject[nCntAll] = CBg::Create(pos, rot, move, size, CBg::TEX(nNumTex));		//���g����
				
				move *= 2.0f;

				if (move.x >= 1.0f)
				{
					move.x = 0.7f;
				}
				if (move.y >= 1.0f)
				{
					move.y = 0.7f;
				}

				nNumTex++;

				if (nNumTex >= CBg::TEX_MAX)
				{
					nNumTex = 0;
				}

				break;
			}
		}
	}

	SetType(TYPE_MULTIBG);

	return S_OK;
}

//====================================
// 2D�|���S���̏���������(�I�o��)
//====================================
HRESULT CMultiBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	pos;
	rot;

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CMultiBg::Uninit(void)
{
	for (int nCntCrt = 0; nCntCrt < MAX_MULTIBG; nCntCrt++)
	{
		if (m_apObject[nCntCrt] != nullptr)
		{
			m_apObject[nCntCrt]->Uninit();
			m_apObject[nCntCrt] = nullptr;
		}
	}

	CObject::Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CMultiBg::Update(void)
{

}

//============================
// 2D�|���S���̕`�揈��
//============================
void CMultiBg::Draw(void)
{

}

//============================
// 2D�|���S���̐�������
//============================
CMultiBg *CMultiBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR2 move, const D3DXVECTOR3 size, int nNum)
{
	CMultiBg *pMultiBg = nullptr;

	if (pMultiBg != nullptr)
	{
		pMultiBg = nullptr;
	}

	pMultiBg = new CMultiBg;

	if (pMultiBg != nullptr)
	{
		pMultiBg->Init(pos,rot,move,size,nNum);
	}
	else
	{
		return nullptr;
	}

	return pMultiBg;
}

//============================
// �j��
//============================
void CMultiBg::Release(int nID)
{
	nID;
}

//============================
// �ʒu�ݒ�
//============================
void CMultiBg::SetPos(const D3DXVECTOR3 pos)
{
	pos;
}

//============================
// �����ݒ�
//============================
void CMultiBg::SetRot(const D3DXVECTOR3 rot)
{
	rot;
}

//============================
// �ʒu�擾
//============================
D3DXVECTOR3 CMultiBg::GetPos(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
// 2D�T�C�Y�擾
//============================
D3DXVECTOR3 CMultiBg::GetSize(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
