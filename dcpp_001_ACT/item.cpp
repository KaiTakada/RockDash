//==================================================
//
// �A�C�e��(item.cpp)
// Author : Kai Takada
//
//==================================================
#include "item.h"
//#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//=======================
// �}�N����`
//=======================
#define PLAYER_EXCESSX (0.0f)						//�v���C���[�̃e�N�X�`���̕��̗]���ȕ�����

//=======================
// �o�C�i���t�@�C����
//=======================
static const char *c_apFileItem[CItem::TYPE_MAX] =
{
	"data\\TEXTURE\\ITEM\\exp.png",		//�ʏ�u���b�N
};

//=======================
// �ÓI�����o�ϐ��錾
//=======================
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX] = {};			//�e�N�X�`���ւ̃|�C���^
int CItem::m_nNumAll = 0;											//���ݎg���Ă���u���b�N��

//=======================
// �R���X�g���N�^
//=======================
CItem::CItem(int nPriority) : CObjectBillboard(nPriority)
{
	m_type = TYPE_EXP;
}

//=======================
// �f�X�g���N�^
//=======================
CItem::~CItem()
{

}

//=======================
// ����������
//=======================
HRESULT CItem::Init(void)
{
	m_type = TYPE_EXP;

	CObjectBillboard::Init();
		
	SetType(TYPE_ITEM);

	return S_OK;
}

//=======================
// ����������
//=======================
HRESULT CItem::Init(const D3DXVECTOR3 pos)
{
	m_type = TYPE_EXP;

	CObjectBillboard::Init(pos);

	SetType(TYPE_ITEM);

	return S_OK;
}

//=======================
// �I������
//=======================
void CItem::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=======================
// �X�V����
//=======================
void CItem::Update(void)
{
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos();

	pos += move;

	SetPos(pos);

	if (CollisionBall())
	{//����=�{��uninit�ς�
		return;
	}

	CObjectBillboard::Update();
}

//=======================
// �`�揈��
//=======================
void CItem::Draw(void)
{
	CObjectBillboard::Draw();
}

//=======================
// �ݒ菈��
//=======================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CItem *pItem = nullptr;

	//�I�u�W�F�N�g����&������
	pItem = new CItem;

	if (pItem != nullptr)
	{
		if (FAILED(pItem->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pItem->SetSize(size);		//�T�C�Y�ݒ�

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pItem->SetIdxTexture(pTexture->Regist(c_apFileItem[type]));
		}
	}
	else
	{
		return nullptr;
	}

	return pItem;
}

//============================
// �����蔻�� (���Ƌ�)
//============================
bool CItem::CollisionBall(void)
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
