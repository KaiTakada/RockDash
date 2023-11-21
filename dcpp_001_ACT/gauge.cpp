//===============================================
//
// �Q�[�W(gauge.cpp) �p�� : objectBillboard
// Author: ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "gauge.h"		//��
#include "texture.h"	//�`��e�N�X�`��
#include "effect.h"		//�O��
#include "particle.h"	//�G�t�F�N�g

//============================
// �}�N����`
//============================
#define NUM_SPEED (20.0f)	//�ړ���
#define NUM_SIZE D3DXVECTOR3(50.0f,50.0f,50.0f)				//�f�t�H���g�T�C�Y
#define FILE_PASS_BAR "data\\TEXTURE\\GAUGE\\bar.png"	//�t�@�C���p�X
#define FILE_PASS_FRAME "data\\TEXTURE\\GAUGE\\frame.png"	//�t�@�C���p�X

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CGauge::m_pTexture = nullptr;				//���ʃe�N�X�`���o�b�t�@

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CGauge::CGauge(int nPriority) : CObject(nPriority)
{
	m_pFrameBB = nullptr;			//�r���{�[�h(�g)
	m_pBarBB = nullptr;			//�r���{�[�h(�_)
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_sizeMax = m_size;
	m_fRat = 0.0f;			//����
}

//============================
// �f�X�g���N�^
//============================
CGauge::~CGauge()
{

}

//====================================
// 2D�e�̏�����(�f�t�H)
//====================================
HRESULT CGauge::Init(void)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRat = 0.0f;

	m_pFrameBB = CObjectBillboard::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f));
	m_pBarBB = CObjectBillboard::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f));

	m_pBarBB->SetLight(true);
	m_pFrameBB->SetLight(true);

	SetType(TYPE_GAUGE);

	return S_OK;
}

//====================================
// 2D�e�̏�����(�ʒu�I�o��)
//====================================
HRESULT CGauge::Init(const D3DXVECTOR3 pos)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRat = 0.0f;

	m_pBarBB = CObjectBillboard::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f), D3DXVECTOR3(NUM_SIZE.x, NUM_SIZE.y, NUM_SIZE.z), true);
	m_pFrameBB = CObjectBillboard::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f), D3DXVECTOR3(NUM_SIZE.x, NUM_SIZE.y, NUM_SIZE.z), true);

	m_pBarBB->SetLight(true);
	m_pFrameBB->SetLight(true);

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	return S_OK;
}

//============================
// 2D�e�̏I��
//============================
void CGauge::Uninit(void)
{
	if (m_pFrameBB != nullptr)
	{
		m_pFrameBB->Uninit();
	}

	if (m_pBarBB != nullptr)
	{
		m_pBarBB->Uninit();
	}

	Release();
}

//============================
// 2D�e�̍X�V
//============================
void CGauge::Update(void)
{
	//if (m_pFrameBB != nullptr)
	//{
	//	m_pFrameBB->Update();
	//}

	//if (m_pBarBB != nullptr)
	//{
	//	m_pBarBB->Update();
	//}
}

//============================
// 2D�e�̕`��
//============================
void CGauge::Draw(void)
{
	//Z�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//Z�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================
// �e�̐���
//============================
CGauge * CGauge::Create( D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const float fRat)
{
	CGauge *pGauge= nullptr;

	//�I�u�W�F�N�g����&������
	pGauge= new CGauge;

	if (pGauge!= nullptr)
	{
		if (FAILED(pGauge->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pGauge->m_fRat = fRat;		//����
			pGauge->m_pBarBB->SetSize(size);		//�T�C�Y�ݒ�
			pGauge->m_pFrameBB->SetSize(size);		//�T�C�Y�ݒ�
			pGauge->SetSizeMax(pGauge->m_pFrameBB->GetSize());

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pGauge->m_pBarBB->SetIdxTexture(pTexture->Regist(FILE_PASS_BAR));
			pGauge->m_pFrameBB->SetIdxTexture(pTexture->Regist(FILE_PASS_FRAME));
		
			pGauge->m_pBarBB->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else
	{
		return nullptr;
	}

	return pGauge;
}

//============================
// �����ݒ�
//============================
void CGauge::SetRatio(float fRat)
{
	if (m_pBarBB != nullptr)
	{
		D3DXVECTOR3 size = m_sizeMax;
		D3DXVECTOR3 pos = m_pBarBB->GetPos();

		size.x *= fRat;
		float fPosX = size.x - m_sizeMax.x;

		//pos.x = fPosX;

		m_fRat = fRat;
		m_pBarBB->SetSize(size);
		//m_pBarBB->SetPos(pos);
	}
}

//============================
// ���W�ݒ�
//============================
void CGauge::SetPos(D3DXVECTOR3 pos)
{
	if (m_pBarBB != nullptr)
	{
		m_pBarBB->SetPos(pos);
	}


	if (m_pFrameBB != nullptr)
	{
		m_pFrameBB->SetPos(pos);
	}
}

//============================
// �o�[�̐F�ݒ�
//============================
void CGauge::SetCol(D3DXCOLOR col)
{
	m_pBarBB->SetColor(col);
}
