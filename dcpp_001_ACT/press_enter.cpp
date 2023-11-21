//===============================================
//
// 2D�|���S��(object2D.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "press_enter.h"
#include "texture.h"

//============================
// �}�N����`
//============================

//============================
// �O���錾
//============================
//class CPlayer;

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^(�f�t�H)
//============================
CPress_Enter::CPress_Enter(int nPriority) : CObject2D(nPriority)
{
	m_nAlphaCnter = 0;						//PRESS ENTER�̓_�ŊԊu�̔���
	m_nTimeInterval = 0;					//PRESS ENTER�̓_�ŊԊu
	m_fAlphaColor = 0.0f;					//���_�J���[
}

//============================
// �f�X�g���N�^
//============================
CPress_Enter::~CPress_Enter()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CPress_Enter::Init(void)
{
	m_nTimeInterval = 25;						//�_�ŊԊu������������
	m_fAlphaColor = 1.0f;
	m_nAlphaCnter = 0;

	CObject2D::Init();

	SetType(TYPE_ENTER);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CPress_Enter::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_nTimeInterval = 25;						//�_�ŊԊu������������
	m_fAlphaColor = 1.0f;
	m_nAlphaCnter = 0;

	CObject2D::Init(pos, rot);

	SetType(TYPE_ENTER);

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CPress_Enter::Uninit(void)
{
	CObject2D::Uninit();

	//���S�t���O�����Ă��Ⴄ
	SetDeath(true);
}

//============================
// 2D�|���S���̍X�V����
//============================
void CPress_Enter::Update(void)
{
	CObject2D::Update();

	m_nAlphaCnter++;

	if (m_nAlphaCnter % m_nTimeInterval == 0)
	{//0.5�b��������

		m_nAlphaCnter = 0;
		D3DXCOLOR col = GetTexCol();

		//col.a = col.a ? 1.0f : 0.0f;
		if (col.a == 0.0f)
		{
			col.a = 1.0f;
		}
		else if (col.a == 1.0f)
		{
			col.a = 0.0f;
		}

		m_fAlphaColor = col.a;

		//col.a = m_fAlphaColor;
		SetTexCol(col);
	}
}

//============================
// 2D�|���S���̕`�揈��
//============================
void CPress_Enter::Draw(void)
{
	CObject2D::Draw();
}

//============================
// 2D�|���S���̐�������
//============================
CPress_Enter * CPress_Enter::Create(void)
{
	CPress_Enter *pEnter;

	//�I�u�W�F�N�g����
	pEnter = new CPress_Enter;

	//������
	pEnter->Init();

	return pEnter;
}

//============================
// 2D�|���S���̐�������
//============================
CPress_Enter * CPress_Enter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	CPress_Enter *pEnter = new CPress_Enter;

	if (pEnter != nullptr)
	{
		pEnter->Init(pos, rot);
		
		pEnter->SetSize(size);

		//�e�N�X�`���t�^
		CTexture *pTexture = CManager::GetInstance()->GetTexture();
		pEnter->SetIdxTexture(pTexture->Regist("data\\TEXTURE\\PressEnter00.png"));
	}
	else
	{
		return nullptr;
	}

	return pEnter;
}
