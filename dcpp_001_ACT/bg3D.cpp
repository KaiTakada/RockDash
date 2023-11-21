//============================
//
// 3D�w�i����(Bg3D.cpp)
// Author: Kai Takada
//
//============================
//==================================
// �C���N���[�h�t�@�C��
//==================================
#include "bg3D.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"
#include "Field.h"

//==================================
// �}�N����`
//==================================
#define TEX_FIELD "data\\TEXTURE\\BG\\bg_001.jpg"
#define DEF_NUM_DIF (8)		//�e�N�X�`���̕�����

//==================================
// �ÓI�����o�ϐ��錾
//==================================

//==================================
// �R���X�g���N�^
//==================================
CBg3D::CBg3D(int nPriority) : CObject3D(nPriority)
{

}

//==================================
// �f�X�g���N�^
//==================================
CBg3D::~CBg3D()
{

}

//==================================
// ����������
//==================================
HRESULT CBg3D::Init(void)
{
	CObject3D::Init();

	SetPos(DEF_VERTEX3D);	//����������
	SetRot(DEF_VERTEX3D);	//����������
	SetSize(D3DXVECTOR3(DEF_SIZE.x, DEF_SIZE.y, 0.0f));

	D3DXVECTOR3 lRot = GetRot();	//����������
	SetRot({ lRot.x, D3DX_PI * 1.0f, lRot.z });	//����������

	SetType(TYPE_FIELD);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CBg3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CObject3D::Init(pos,rot);

	D3DXVECTOR3 lRot = GetRot();	//����������
	SetRot({ D3DX_PI * -0.5f, lRot.y, lRot.z });	//����������
												
	//�T�C�Y�ݒ�
	SetSize(D3DXVECTOR3(DEF_SIZE.x, 0.0f, DEF_SIZE.z));

	SetType(TYPE_FIELD);

	return S_OK;
}

//==================================
// �I������
//==================================
void CBg3D::Uninit(void)
{
	CObject3D::Uninit();
}

//==================================
// �X�V����
//==================================
void CBg3D::Update(void)
{
	CObject3D::Update();
}

//==================================
// �`�揈��
//==================================
void CBg3D::Draw(void)
{
	CObject3D::Draw();
}

//============================
// ��������
//============================
CBg3D * CBg3D::Create(void)
{
	CBg3D *pField;

	//�I�u�W�F�N�g����
	pField = new CBg3D;

	//������
	pField->Init();

	return pField;
}

//============================
// ��������
//============================
CBg3D * CBg3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CBg3D *pBg = nullptr;

	//�I�u�W�F�N�g����&������
	pBg = new CBg3D;

	if (pBg != nullptr)
	{
		pBg->Init(pos, rot);

		pBg->SetSize(size);

		float fposZ = DEF_FIELD_SIZE.z;

		pBg->SetPos({ pos.x, pos.y + fposZ, pos.z + fposZ });

		int tex0 = int(size.x / 256.0f);
		int tex1 = int(size.z / 256.0f);
		pBg->SetDivTex(tex0, tex1);

		CTexture *pTexture = CManager::GetInstance()->GetTexture();
		pBg->SetIdxTexture(pTexture->Regist(TEX_FIELD));
	}
	else
	{
		return nullptr;
	}

	return pBg;
}
