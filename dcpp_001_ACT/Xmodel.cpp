//============================
//
// X���f���̏���(model.cpp)
// Author: Kai Takada
//
//============================
#include "manager.h"
#include "Xmodel.h"

//===============================
// �}�N����`
//===============================

//============================
// �ÓI�����o�ϐ��錾
//============================
int CXModel::m_nNumAll = 0;				//���ʃe�N�X�`���o�b�t�@

//============================
// �e�N�X�`���p�X
//============================
const char *c_apXFilepass[] =
{
	"data\\MODEL\\null.x"
};

//=================================
// �R���X�g���N�^
//=================================
CXModel::CXModel()
{
	for (int nCntUnload = 0; nCntUnload < MAX_XMODEL; nCntUnload++)
	{
		//�f�[�^�j��
		m_aModel[nCntUnload].pBuffMat = nullptr;
		m_aModel[nCntUnload].pTexture = nullptr;
		m_aModel[nCntUnload].pMesh = nullptr;

		m_aModel[nCntUnload].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aModel[nCntUnload].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aModel[nCntUnload].mtxWorld = {};
		m_aModel[nCntUnload].dwNumMat = 0;

		//�f�[�^�j��
		m_apFilename[nCntUnload] = nullptr;
	}
}

//=================================
// �f�X�g���N�^
//=================================
CXModel::~CXModel()
{
	m_nNumAll--;
}

//=================================
// �e�N�X�`���ǂݍ���
//=================================
HRESULT CXModel::Load(void)
{
	for (int nCntFile = 0; nCntFile < sizeof(c_apXFilepass) / sizeof(c_apXFilepass[0]); nCntFile++)
	{
		//m_apFilename[nCntFile] = new char;

		Regist(c_apXFilepass[nCntFile]);
	}

	return S_OK;
}

//=================================
// �e�N�X�`���j��
//=================================
void CXModel::Unload(void)
{
	for (int nCntFile = 0; nCntFile < MAX_XMODEL; nCntFile++)
	{
		if (m_apFilename[nCntFile] != nullptr)
		{
			//delete�Ŕj�󂳂�Ă���
			delete m_apFilename[nCntFile];
			m_apFilename[nCntFile] = nullptr;
		}
	}

	for (int nCntUnload = 0; nCntUnload < MAX_XMODEL; nCntUnload++)
	{
		//�e�N�X�`���j��
		if (m_aModel[nCntUnload].pMesh != nullptr)
		{
			m_aModel[nCntUnload].pMesh->Release();
			m_aModel[nCntUnload].pMesh = nullptr;
		}

		if (m_aModel[nCntUnload].pBuffMat != nullptr)
		{
			m_aModel[nCntUnload].pBuffMat->Release();
			m_aModel[nCntUnload].pBuffMat = nullptr;
		}

		if (m_aModel[nCntUnload].pTexture != nullptr)
		{
			for (int nCntTex = 0; nCntTex < int(m_aModel[nCntUnload].dwNumMat); nCntTex++)
			{
				if (m_aModel[nCntUnload].pTexture[nCntTex] != nullptr)
				{
					m_aModel[nCntUnload].pTexture[nCntTex]->Release();
					m_aModel[nCntUnload].pTexture[nCntTex] = nullptr;
				}
			}

			delete m_aModel[nCntUnload].pTexture;
			m_aModel[nCntUnload].pTexture = nullptr;
		}
	}
}

//============================
// ���f���ǉ��Ǎ�
//============================
int CXModel::Regist(const char *pFilename, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	int nNumVtx = 0;		//���_��
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	int nCntReg = 0;

	for (nCntReg = 0; nCntReg < MAX_XMODEL; nCntReg++)
	{
		if (m_aModel[nCntReg].pMesh != nullptr &&
			strcmp(m_apFilename[nCntReg],(char*)(pFilename)) == 0)
		{//��񂪓����Ă���
			
			vtxMin = &m_aModel[nCntReg].vtxMin;
			vtxMax = &m_aModel[nCntReg].vtxMax;

			return nCntReg;
		}
		if (m_aModel[nCntReg].pMesh == nullptr)
		{//��񂪓����Ă��Ȃ�
			break;
		}
	}

	if (nCntReg >= MAX_XMODEL)
	{//�������锠���Ȃ���
	
		if (m_aModel[0].pMesh != nullptr)
		{//0�Ԃ�����ɓǂݍ��߂Ă�����
			return 0;
		}
		else
		{
			return -1;
		}
	}

	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aModel[nCntReg].pBuffMat,
		NULL,
		&m_aModel[nCntReg].dwNumMat,
		&m_aModel[nCntReg].pMesh)))
	{
		return 0;
	}

	//�}�e���A�����ɑ΂���|�C���^���擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_aModel[nCntReg].pBuffMat->GetBufferPointer();

	if (m_aModel[nCntReg].pTexture != nullptr)
	{
		m_aModel[nCntReg].pTexture = nullptr;
	}

	m_aModel[nCntReg].pTexture = new LPDIRECT3DTEXTURE9[(int)m_aModel[nCntReg].dwNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_aModel[nCntReg].dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
		 //�e�N�X�`���̓ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,				//�e�N�X�`���̃t�@�C����
				&m_aModel[nCntReg].pTexture[nCntMat])))	//�e�N�X�`���p�X���Ԉ���Ă���ƕ`�掞�ɉ���(breakpoint)
			{
				m_aModel[nCntReg].pTexture[nCntMat] = nullptr;
			}
		}
		else
		{
			m_aModel[nCntReg].pTexture[nCntMat] = nullptr;
		}
	}

	//���_�����擾
	nNumVtx = m_aModel[nCntReg].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_aModel[nCntReg].pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_aModel[nCntReg].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

		//���ׂĂ̒��_���r���ēG�̍ŏ��l�E�ő�l�𔲂��o��
		if (m_aModel[nCntReg].vtxMax.x < vtx.x)
		{
			m_aModel[nCntReg].vtxMax.x = vtx.x;
		}
		if (m_aModel[nCntReg].vtxMax.y < vtx.y)
		{
			m_aModel[nCntReg].vtxMax.y = vtx.y;
		}
		if (m_aModel[nCntReg].vtxMax.z < vtx.z)
		{
			m_aModel[nCntReg].vtxMax.z = vtx.z;
		}

		if (m_aModel[nCntReg].vtxMin.x > vtx.x)
		{
			m_aModel[nCntReg].vtxMin.x = vtx.x;
		}
		if (m_aModel[nCntReg].vtxMin.y > vtx.y)
		{
			m_aModel[nCntReg].vtxMin.y = vtx.y;
		}
		if (m_aModel[nCntReg].vtxMin.z > vtx.z)
		{
			m_aModel[nCntReg].vtxMin.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_aModel[nCntReg].pMesh->UnlockVertexBuffer();

	vtxMin = &m_aModel[nCntReg].vtxMin;
	vtxMax = &m_aModel[nCntReg].vtxMax;

	m_apFilename[nCntReg] = new char[int(strlen(pFilename)) + 1];
	strcpy(m_apFilename[nCntReg], pFilename);

	m_nNumAll++;
	return nCntReg;
}

//============================
//�e�N�X�`�����擾
//============================
CXModel::Model *CXModel::GetAddress(int nIdx)
{
	return &m_aModel[nIdx]; 
}
