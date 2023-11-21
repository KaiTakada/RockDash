//============================
//
// X���f���̏���(model.cpp)
// Author: Kai Takada
//
//============================
#include "manager.h"
#include "objectX.h"
#include "Xmodel.h"

//===============================
// �}�N����`
//===============================

//=================================
// �R���X�g���N�^
//=================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_nIdxModel = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = m_pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=================================
// �f�X�g���N�^
//=================================
CObjectX::~CObjectX()
{

}

//=================================
// �v���C���[�̏���������
//=================================
HRESULT CObjectX::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);		//����������
	m_posOld = m_pos;		//����������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����������
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=================================
// �v���C���[�̏���������
//=================================
HRESULT CObjectX::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)		//������(�I�o��)
{
	m_pos = pos;		//����������
	m_posOld = m_pos;		//����������
	m_rot = rot;		//����������
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=================================
// �v���C���[�̏I������
//=================================
void CObjectX::Uninit(void)
{
	//���S�t���O�����Ă��Ⴄ
	SetDeath(true);

	Release();
}

//=================================
// �v���C���[�̍X�V����
//=================================
void CObjectX::Update(void)
{
	//�O��̈ʒu���X�V
	m_posOld = m_pos;
}

//=================================
// �v���C���[�̕`�揈��
//=================================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	CXModel::Model *pModel = pXModel->GetAddress(m_nIdxModel);


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pModel->mtxWorld);

	//�T�C�Y���f
	D3DXMatrixScaling(&mtxScal,
		m_size.x, m_size.y, m_size.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxScal);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &pModel->mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pModel->dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pModel->pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		pModel->pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=================================
// �v���C���[�̕`�揈��(�F�w��)
//=================================
void CObjectX::Draw(const D3DMATERIAL9 mat)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	CXModel::Model *pModel = pXModel->GetAddress(m_nIdxModel);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pModel->mtxWorld);

	//�T�C�Y���f
	D3DXMatrixScaling(&mtxScal,
		m_size.x, m_size.y, m_size.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxScal);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&pModel->mtxWorld, &pModel->mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &pModel->mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pModel->dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&mat);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pModel->pTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		pModel->pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=================================
// �T�C�Y�ݒ�
//=================================
void CObjectX::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	//�T�C�Y��vtx�̂��荇�킹
	//operator�ňꊇ������悤�ɂ���
	m_vtxMax.x = m_size.x * m_vtxMax.x;
	m_vtxMax.y = m_size.y * m_vtxMax.y;
	m_vtxMax.z = m_size.z * m_vtxMax.z;

	m_vtxMin.x = m_size.x * m_vtxMin.x;
	m_vtxMin.y = m_size.y * m_vtxMin.y;
	m_vtxMin.z = m_size.z * m_vtxMin.z;
}

//=================================
// ����
//=================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pModel;

	//�I�u�W�F�N�g����
	pModel = new CObjectX;

	//������
	pModel->Init();

	return pModel;
}

//=================================
// ����
//=================================
CObjectX *CObjectX::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fSize)
{
	CObjectX *pObjectX = nullptr;
	
	fSize;

	//�I�u�W�F�N�g����&������
	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->Init(pos, rot);
	}
	else
	{
		return nullptr;
	}

	return pObjectX;
}
