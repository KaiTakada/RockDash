//===============================================
//
// ���ʃ|���S��(effect.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "effect.h"
#include "texture.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[CEffect::TEX_MAX] = {};

//============================
// �t�@�C������`
//============================
static const char *c_apTexpass[CEffect::TEX_MAX] =
{
	"data\\TEXTURE\\EFFECT\\effect000.jpg",
	"data\\TEXTURE\\EFFECT\\effect002.jpg",
};

//============================
// �R���X�g���N�^
//============================
CEffect::CEffect(int nPriority) : CObjectBillboard(nPriority)
{
	m_nLife = 0;
	m_nLifeMax = 0;
	m_type = TEX_000;
}

//============================
// �f�X�g���N�^
//============================
CEffect::~CEffect()
{

}

//====================================
// �G�t�F�N�g�̏���������(�f�t�H)
//====================================
HRESULT CEffect::Init(void)
{
	CObjectBillboard::Init();

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�ړ���
	m_nLife = 0;		//�c�����
	m_nLifeMax = 0;		//����

	CObjectBillboard::SetZtest(true);
	CObjectBillboard::SetAbrend(true);

	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//====================================
// �G�t�F�N�g�̏�����(�ʒu�I�o��)
//====================================
HRESULT CEffect::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	if (FAILED(CObjectBillboard::Init()))
	{
		return E_FAIL;
	}

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�ړ���
	m_nLife = 0;		//�c�����
	m_nLifeMax = 0;		//����

	CObjectBillboard::SetPos(pos);
	CObjectBillboard::SetRot(rot);
	CObjectBillboard::SetSize(D3DXVECTOR3(DEF_BBSIZE.x, DEF_BBSIZE.y, 0.0f));
	CObjectBillboard::SetZtest(true);
	CObjectBillboard::SetAbrend(true);

	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//============================
// �G�t�F�N�g�̏I������
//============================
void CEffect::Uninit(void)
{
	//���g�̔j��
	CObjectBillboard::Uninit();
}

//============================
// �G�t�F�N�g�̍X�V����
//============================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	pos += GetMove();

	//�ʒu�ς�
	SetPos(pos);

	//�T�C�Y�ς�
	size.x *= (float)m_nLife / (float)m_nLifeMax;
	size.y *= (float)m_nLife / (float)m_nLifeMax;
	SetSize(size);

	//��ʊO����


	if (size.x <= 1.1f ||
		size.y <= 1.1f)
	{
		Uninit();
		return;
	}

	//����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	m_nLife--;
}

//============================
// �G�t�F�N�g�̕`�揈��
//============================
void CEffect::Draw(void)
{
	CObjectBillboard::Draw();
}

//============================
// �G�t�F�N�g�̐�������
//============================
CEffect * CEffect::Create(void)
{
	CEffect *pEffect;

	//�I�u�W�F�N�g����
	pEffect = new CEffect;

	//������
	pEffect->Init();

	return pEffect;
}

//============================
// �G�t�F�N�g�̐�������
//============================
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 size, int nLife, const TEX TexType)
{
	CEffect *pEffect = nullptr;

	//�I�u�W�F�N�g����&������
	if (pEffect == nullptr)
	{
		pEffect = new CEffect;

		if (pEffect != nullptr)
		{//�����o������

			if (FAILED(pEffect->Init(pos, rot)))
			{
				pEffect->Uninit();
				return nullptr;
			}

			pEffect->SetSize(size);

			pEffect->SetMove(move);
			pEffect->m_nLife = nLife;
			pEffect->m_nLifeMax = nLife;
			pEffect->m_type = TexType;

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pEffect->SetIdxTexture(pTexture->Regist(c_apTexpass[TexType]));
		}
		else
		{//�����o����
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	return pEffect;
}
