//===============================================
//
// ���G�t�F�N�g(ef_smoke.cpp) �p�� : effect
// Author: ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "ef_smoke.h"		//��
#include "texture.h"	//�`��e�N�X�`��
#include "game.h"	//�Q�[��
#include "player.h"	//�v���C���[

//============================
// �}�N����`
//============================
#define NUM_SPEED (20.0f)	//�ړ���
#define NUM_SIZE D3DXVECTOR3(50.0f,50.0f,50.0f)				//�f�t�H���g�T�C�Y

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �t�@�C������`
//============================
static const char *c_pTexSmoke = "data\\TEXTURE\\EFFECT\\effect002.jpg";

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CEf_Smoke::CEf_Smoke(int nPriority) : CEffect(nPriority)
{

}

//============================
// �f�X�g���N�^
//============================
CEf_Smoke::~CEf_Smoke()
{

}

//====================================
// ���̏�����(�f�t�H)
//====================================
HRESULT CEf_Smoke::Init(void)
{
	CEffect::Init();

	//�F
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//====================================
// ���̏�����(�ʒu�I�o��)
//====================================
HRESULT CEf_Smoke::Init(const D3DXVECTOR3 pos)
{
	CEffect::Init(pos);

	//�F
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�^�C�v�ݒ�
	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//============================
// ���̏I��
//============================
void CEf_Smoke::Uninit(void)
{
	CEffect::Uninit();
}

//============================
// ���̍X�V
//============================
void CEf_Smoke::Update(void)
{
	//�ʒu�ς�
	D3DXVECTOR3 pos = GetPos();
	pos += GetMove();
	SetPos(pos);

	//�T�C�Y�ς�
	D3DXVECTOR3 size = GetSize();
	size *= 1.07f;
	SetSize(size);

	//�F��
	D3DXCOLOR col = GetColor();
	col.r *= 0.95f;
	col.g *= 0.95f;
	col.b *= 0.95f;
	SetColor(col);

	//����
	int nLife = GetLife();
	if (nLife <= 0)
	{
		Uninit();
		return;
	}

	//�������
	nLife--;
	SetLife(nLife);
}

//============================
// ���̕`��
//============================
void CEf_Smoke::Draw(void)
{
	CEffect::Draw();
}

//============================
// ���̐���
//============================
CEf_Smoke * CEf_Smoke::Create( D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CEf_Smoke *pSmoke= nullptr;

	//�I�u�W�F�N�g����&������
	pSmoke= new CEf_Smoke;

	if (pSmoke!= nullptr)
	{
		if (FAILED(pSmoke->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pSmoke->SetSize(size);
			pSmoke->SetLight(true);

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pSmoke->SetIdxTexture(pTexture->Regist(c_pTexSmoke));
		}
	}
	else
	{
		return nullptr;
	}

	return pSmoke;
}
