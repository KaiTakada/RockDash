//============================
//
// �n�ʏ���(Field.cpp)
// Author: Kai Takada
//
//============================
//==================================
// �C���N���[�h�t�@�C��
//==================================
#include "Field.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"

//==================================
// �}�N����`
//==================================
#define TEX_FIELD "data\\TEXTURE\\FIELD\\rock.jpg"
#define DEF_NUM_DIF (8)

//==================================
// �ÓI�����o�ϐ��錾
//==================================

//==================================
// �R���X�g���N�^
//==================================
CField::CField(int nPriority) : CObject3D(nPriority)
{

}

//==================================
// �f�X�g���N�^
//==================================
CField::~CField()
{

}

//==================================
// ����������
//==================================
HRESULT CField::Init(void)
{
	CObject3D::Init();

	SetPos(DEF_VERTEX3D);	//����������
	SetRot(DEF_VERTEX3D);	//����������
	SetSize(D3DXVECTOR3(DEF_SIZE.x, DEF_SIZE.y, 0.0f));

	SetType(TYPE_FIELD);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CField::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CObject3D::Init(pos,rot);

	//�T�C�Y�ݒ�
	SetSize(D3DXVECTOR3(DEF_SIZE.x, 0.0f, DEF_SIZE.z));

	SetType(TYPE_FIELD);

	return S_OK;
}

//==================================
// �I������
//==================================
void CField::Uninit(void)
{
	CObject3D::Uninit();
}

//==================================
// �X�V����
//==================================
void CField::Update(void)
{
	CObject3D::Update();
}

//==================================
// �`�揈��
//==================================
void CField::Draw(void)
{
	CObject3D::Draw();
}

//============================
// ��������
//============================
CField * CField::Create(void)
{
	CField *pField;

	//�I�u�W�F�N�g����
	pField = new CField;

	//������
	pField->Init();

	return pField;
}

//============================
// ��������
//============================
CField * CField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CField *pField = nullptr;

	//�I�u�W�F�N�g����&������
	pField = new CField;

	if (pField != nullptr)
	{
		pField->Init(pos, rot);

		pField->SetSize(size);

		int tex0 = int(size.x / 256.0f);
		int tex1 = int(size.z / 256.0f);
		pField->SetDivTex(tex0, tex1);

		CTexture *pTexture = CManager::GetInstance()->GetTexture();
		pField->SetIdxTexture(pTexture->Regist(TEX_FIELD));
	}
	else
	{
		return nullptr;
	}

	return pField;
}
