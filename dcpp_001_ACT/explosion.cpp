//===============================================
//
// ����(explosion.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "explosion.h"
#include "texture.h"
#include "Anim.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = nullptr;				//���ʃe�N�X�`���o�b�t�@
int CExplosion::m_nNumAll = 0;		//����

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CExplosion::CExplosion(int nPriority) : CObjectBillboardAnim(nPriority)
{
	m_nNumAll++;
}

//============================
// �f�X�g���N�^
//============================
CExplosion::~CExplosion()
{
	m_nNumAll--;
}

//====================================
// 2D�e�̏�����(�f�t�H)
//====================================
HRESULT CExplosion::Init(void)
{
	//������
	CObjectBillboardAnim::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//====================================
// 2D�e�̏�����(�ʒu�I�o��)
//====================================
HRESULT CExplosion::Init(const D3DXVECTOR3 pos)
{
	//������
	if(FAILED(CObjectBillboardAnim::Init(pos)))
	{
		return E_FAIL;
	}

	//�T�C�Y�ݒ�
	SetSize(D3DXVECTOR3(DEF_SIZE_ANIM.x, DEF_SIZE_ANIM.y, 0.0f));



	//�^�C�v�ݒ�
	SetType(TYPE_EXPLOSION);

	return S_OK;
}

//============================
// 2D�e�̏I��
//============================
void CExplosion::Uninit(void)
{
	//�I��
	CObjectBillboardAnim::Uninit();
}

//============================
// 2D�e�̍X�V
//============================
void CExplosion::Update(void)
{
	CObjectBillboardAnim::Update();
	CAnim *pAnim = CObjectBillboardAnim::GetAnim();

	//���[�v����
	if (pAnim->GetNumLoop() == 0)
	{
		Uninit();
	}
}

//============================
// 2D�e�̕`��
//============================
void CExplosion::Draw(void)
{
	//�`��
	CObjectBillboardAnim::Draw();
}

//============================
// �e�̐���
//============================
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nFrame, const int nLoop, const int nNumPtnX, const int nNumPtnY)
{
	CExplosion *pExplosion = nullptr;

	//�I�u�W�F�N�g����&������
	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		if (FAILED(pExplosion->Init(pos)))
		{
			pExplosion->Uninit();
			return nullptr;
		}
		else
		{

			CAnim *pAnim = pExplosion->GetAnim();

			pAnim->SetNumPtnX(nNumPtnX);		//�p�^�[�����ݒ�
			pAnim->SetNumPtnY(nNumPtnY);
			pAnim->SetNumFrame(nFrame);		//�t���[�����ݒ�
			pAnim->SetNumLoop(nLoop);		//���[�v���ݒ�

			pExplosion->SetLight(true);

			pExplosion->SetTexPos(D3DXVECTOR2(1.0f / nNumPtnX, 1.0f / nNumPtnY), D3DXVECTOR2(0.0f, 0.0f));	//�e�N�X�`���T�C�Y�ݒ�

			pExplosion->SetSize(size);		//�T�C�Y�ݒ�

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pExplosion->SetIdxTexture(pTexture->Regist("data\\TEXTURE\\explosion000.png"));
		}
	}
	else
	{
		return nullptr;
	}

	return pExplosion;
}
