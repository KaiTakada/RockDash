//===============================================
//
// �o���l�I�[�u(experience.cpp) �p�� : effect
// Author: ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "experience.h"		//��
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
LPDIRECT3DTEXTURE9 CExperience::m_pTexture = nullptr;				//���ʃe�N�X�`���o�b�t�@

//============================
// �t�@�C������`
//============================
static const char *c_pTexExp = "data\\TEXTURE\\EXP\\exp.png";

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CExperience::CExperience(int nPriority) : CEffect(nPriority)
{
	m_fValue = 0.0f;			//����
}

//============================
// �f�X�g���N�^
//============================
CExperience::~CExperience()
{

}

//====================================
// �o���l�̏�����(�f�t�H)
//====================================
HRESULT CExperience::Init(void)
{
	m_fValue = 0.0f;

	CEffect::Init();

	CObject::SetType(TYPE_EXP);

	return S_OK;
}

//====================================
// �o���l�̏�����(�ʒu�I�o��)
//====================================
HRESULT CExperience::Init(const D3DXVECTOR3 pos)
{
	m_fValue = 0.0f;

	CEffect::Init(pos);

	//CObjectBillboard::SetAbrend(false);

	//�^�C�v�ݒ�
	CObject::SetType(TYPE_EXP);

	return S_OK;
}

//============================
// �o���l�̏I��
//============================
void CExperience::Uninit(void)
{
	CEffect::Uninit();
}

//============================
// �o���l�̍X�V
//============================
void CExperience::Update(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos();

	pos += move;

	SetPos(pos);

	CollisionBall();
}

//============================
// �o���l�̕`��
//============================
void CExperience::Draw(void)
{
	CEffect::Draw();
}

//============================
// �o���l�̐���
//============================
CExperience * CExperience::Create( D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float fValue)
{
	CExperience *pExp= nullptr;

	//�I�u�W�F�N�g����&������
	pExp= new CExperience;

	if (pExp!= nullptr)
	{
		if (FAILED(pExp->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pExp->m_fValue = fValue;		//����
			pExp->SetSize(size);
			pExp->SetLight(true);

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pExp->SetIdxTexture(pTexture->Regist(c_pTexExp));
		}
	}
	else
	{
		return nullptr;
	}

	return pExp;
}

//============================
// �����蔻�� (���Ƌ�)
//============================
bool CExperience::CollisionBall(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Objsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_PLAYER)
				{//�v���C���\��������
					Objpos = pObject->GetPos();
					Objsize = pObject->GetSize();

					CPlayer *pPlayer = CGame::GetPlayer();
					Objpos.y += pPlayer->GetHeartPos();

					float fSize0 = (size.x + size.z) * 0.5f;		//�A�C�e���̔��axz
					float fSize1 = (size.x + size.y) * 0.5f;		//�A�C�e���̔��axy
					float fSize2 = (size.z + size.y) * 0.5f;		//�A�C�e���̔��azy

					float fObjsize0 = (Objsize.x + Objsize.z) * 0.5f;		//�I�u�W�F�N�g�̔��axz
					float fObjsize1 = (Objsize.x + Objsize.y) * 0.5f;		//�I�u�W�F�N�g�̔��axy
					float fObjsize2 = (Objsize.z + Objsize.y) * 0.5f;		//�I�u�W�F�N�g�̔��azy

					float fColl0 = fSize0 + fObjsize0;		//�����蔻��͈�
					float fColl1 = fSize1 + fObjsize1;		//�����蔻��͈�
					float fColl2 = fSize2 + fObjsize2;		//�����蔻��͈�

					float fLength0 = hypotf((pos.x - Objpos.x), (pos.z - Objpos.z));		//2�_�Ԃ̒���xz
					float fLength1 = hypotf((pos.x - Objpos.x), (pos.y - Objpos.y));		//2�_�Ԃ̒���xy
					float fLength2 = hypotf((pos.z - Objpos.z), (pos.y - Objpos.y));		//2�_�Ԃ̒���zy

					if (fLength0 <= fColl0 &&
						fLength1 <= fColl1 &&
						fLength2 <= fColl2)
					{
						//�e�I��
						Uninit();

						return TRUE;
					}
				}
				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	return FALSE;
}
