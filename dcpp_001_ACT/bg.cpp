//===============================================
//
// �w�i(bg.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "bg.h"
#include "multibg.h"
#include "texture.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CBg::m_pTexture[CBg::TEX_MAX] = {};

//============================
// �t�@�C������`
//============================
static const char *c_apTexpass[CBg::TEX_MAX] =
{
	"data\\TEXTURE\\bg100.png",
	"data\\TEXTURE\\bg101.png",
	"data\\TEXTURE\\bg102.png",
};

//============================
// �R���X�g���N�^
//============================
CBg::CBg()
{
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//============================
// �f�X�g���N�^
//============================
CBg::~CBg()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CBg::Init(void)
{
	CObject2D::Init();

	SetType(TYPE_BG);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CBg::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CObject2D::Init();

	CObject2D::SetPos(pos);
	CObject2D::SetRot(rot);
	CObject2D::SetSize(D3DXVECTOR3(DEF_SIZE_STATIC.x, DEF_SIZE_STATIC.y, 0.0f));

	SetType(TYPE_BG);

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CBg::Uninit(void)
{
	//���g�̔j��
	CObject2D::Uninit();

	//Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CBg::Update(void)
{
	D3DXVECTOR2 texPosleftUp = GetTexPosleftUp();
	D3DXVECTOR2 texPosrightDown = GetTexPosrightDown();

	D3DXVECTOR2 move = m_texMove * 0.01f;

	texPosleftUp += move;
	texPosrightDown += move;

	//texPosleftUp += m_texMove;
	//texPosrightDown += m_texMove;


	if (texPosleftUp.x >= 1.0f - GetTexPosDif().x)
	{
		texPosleftUp.x = 0.0f;
	}
	if (texPosleftUp.y >= 1.0f - GetTexPosDif().y)
	{
		texPosleftUp.y = 0.0f;
	}

	if (texPosrightDown.x >= 1.0f - GetTexPosDif().x)
	{
		texPosrightDown.x = 1.0f;
	}
	if (texPosrightDown.y >= 1.0f - GetTexPosDif().y)
	{
		texPosrightDown.y = 1.0f;
	}

	SetTexPos(texPosrightDown, texPosleftUp);
}

//============================
// 2D�|���S���̕`�揈��
//============================
void CBg::Draw(void)
{
	CObject2D::Draw();
}

//============================
// 2D�|���S���̐�������
//============================
CBg * CBg::Create(void)
{
	CBg *pBg;

	//�I�u�W�F�N�g����
	pBg = new CBg;

	//������
	pBg->Init();

	return pBg;
}

//============================
// 2D�|���S���̐�������
//============================
CBg * CBg::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 move, const D3DXVECTOR3 size, const TEX TexType)
{
	CBg *pBg = nullptr;

	//�I�u�W�F�N�g����&������
	if (pBg == nullptr)
	{
		pBg = new CBg;

		if (pBg != nullptr)
		{
			pBg->Init(pos, rot);

			pBg->SetSize(size);

			pBg->SetTexPos(D3DXVECTOR2(1.0f,1.0f), D3DXVECTOR2(0.0f, 0.0f));

			pBg->m_texMove = move;

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pBg->SetIdxTexture(pTexture->Regist(c_apTexpass[TexType]));
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	return pBg;
}
