//===============================================
//
// ����(number.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "item2D.h"
#include "object.h"
#include "texture.h"
#include "player.h"
#include "weapon.h"
#include "game.h"

//============================
// �}�N����`
//============================
#define NUM_SPEED (0.0f)	//�ړ���
#define NUM_SIZE D3DXVECTOR2(100.0f,100.0f)				//�f�t�H���g�T�C�Y

//============================
// �e�N�X�`���p�X
//============================
static const char *c_apTexpassItem2D[CItem2D::TYPE_MAX] =
{
	"data\\TEXTURE\\ITEM\\000_heal.png",
	"data\\TEXTURE\\ITEM\\001_powerup.png",
	"data\\TEXTURE\\ITEM\\002_speedup.png",
	"data\\TEXTURE\\ITEM\\004_Cooltime.png",
};

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CItem2D::m_pTexture = nullptr;				//���ʃe�N�X�`���o�b�t�@

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CItem2D::CItem2D()
{
	m_type = CItem2D::TYPE_000_HEAL;
}

//============================
// �f�X�g���N�^
//============================
CItem2D::~CItem2D()
{

}

//====================================
// ������(�f�t�H)
//====================================
HRESULT CItem2D::Init(void)
{
	//������
	CObject2D::Init();

	CObject::SetType(TYPE_ITEM2D);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CItem2D::Init(const D3DXVECTOR3 pos)
{
	//������
	if(FAILED(CObject2D::Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f))))
	{
		return E_FAIL;
	}

	//�^�C�v�ݒ�
	CObject::SetType(TYPE_ITEM2D);

	//�T�C�Y�ݒ�
	SetSize(D3DXVECTOR3(NUM_SIZE.x, NUM_SIZE.y, 0.0f));

	return S_OK;
}

//============================
// �I��
//============================
void CItem2D::Uninit(void)
{
	//�I��
	CObject2D::Uninit();
}

//============================
// �X�V
//============================
void CItem2D::Update(void)
{
	//�X�V
	CObject2D::Update();
}

//============================
// �`��
//============================
void CItem2D::Draw(void)
{
	//�`��
	CObject2D::Draw();
}

//============================
// ����
//============================
CItem2D *CItem2D::Create(const D3DXVECTOR3 pos, const TYPE type, const D3DXVECTOR3 size)
{
	CItem2D *pNumber = nullptr;

	//�I�u�W�F�N�g����&������
	pNumber = new CItem2D;

	if (pNumber != nullptr)
	{
		if (FAILED(pNumber->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pNumber->SetSize(size);		//�T�C�Y�ݒ�

			pNumber->m_type = type;

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pNumber->SetIdxTexture(pTexture->Regist(c_apTexpassItem2D[type]));
		}
	}
	else
	{
		return nullptr;
	}

	return pNumber;
}

//============================
// �C�ӂ̐��l��`��ʒu�ݒ�
//============================
void CItem2D::SetType(TYPE type)
{
	m_type = type;

	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CObject2D::SetIdxTexture(pTexture->Regist(c_apTexpassItem2D[type]));
}

//============================
// �v���C���[�ɑΏۂ�^����
//============================
void CItem2D::PlayerAdd()
{
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr)
	{
		return;
	}

	CPlayer::Param param = pPlayer->GetParam();

	switch (m_type)
	{
	case CItem2D::TYPE_000_HEAL:
		param.fLife += 30.0f;
		pPlayer->Damage(-30.0f);
		break;
	case CItem2D::TYPE_001_ATTACK:
		param.fAttack += 1.0f;
		break;
	case CItem2D::TYPE_002_SPEED:
		param.fSpeed *= 1.1f;
		break;
	default:
		assert(false);
		break;
	}

	pPlayer->SetParam(param);
}
