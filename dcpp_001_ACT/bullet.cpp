//===============================================
//
// �e(bullet.cpp) �p�� : objectBillboard
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "bullet.h"		//��
#include "texture.h"	//�`��e�N�X�`��
#include "effect.h"		//�O��
#include "particle.h"	//�G�t�F�N�g
#include "explosion.h"	//�G�t�F�N�g
#include "game.h"		//�X�R�A���Z
#include "score.h"		//�X�R�A���Z
#include "object.h"		//�����蔻��
#include "enemy.h"		//�����蔻��
#include "player.h"		//�����蔻��

//============================
// �}�N����`
//============================
#define NUM_SPEED (20.0f)	//�ړ���
#define NUM_SIZE D3DXVECTOR3(50.0f,50.0f,50.0f)				//�f�t�H���g�T�C�Y
#define FILE_PASS "data\\TEXTURE\\bullet000.png"	//�t�@�C���p�X

//============================
// �ÓI�����o�ϐ��錾
//============================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = nullptr;				//���ʃe�N�X�`���o�b�t�@
int CBullet::m_nNumAll = 0;		//����

//============================================
//==================== �e ====================
//============================
// �R���X�g���N�^
//============================
CBullet::CBullet(int nPriority) : CObjectBillboard(nPriority)
{
	m_nLife = 0;
	m_nEffCtr = 0;
	m_side = SIDE_NONE;
	m_nDamage = 0;

	m_nNumAll++;
}

//============================
// �f�X�g���N�^
//============================
CBullet::~CBullet()
{
	m_nNumAll--;
}

//====================================
// 2D�e�̏�����(�f�t�H)
//====================================
HRESULT CBullet::Init(void)
{
	//������
	CObjectBillboard::Init();

	CObjectBillboard::SetLight(true);

	SetType(TYPE_BULLET);

	return S_OK;
}

//====================================
// 2D�e�̏�����(�ʒu�I�o��)
//====================================
HRESULT CBullet::Init(const D3DXVECTOR3 pos)
{
	//������
	if(FAILED(CObjectBillboard::Init(pos)))
	{
		return E_FAIL;
	}

	CObjectBillboard::SetLight(true);

	//�^�C�v�ݒ�
	SetType(TYPE_BULLET);

	//�T�C�Y�ݒ�
	SetSize(D3DXVECTOR3(NUM_SIZE.x, NUM_SIZE.y, NUM_SIZE.z));

	return S_OK;
}

//============================
// 2D�e�̏I��
//============================
void CBullet::Uninit(void)
{
	//�I��
	CObjectBillboard::Uninit();
}

//============================
// 2D�e�̍X�V
//============================
void CBullet::Update(void)
{
	//���W�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	pos += GetMove();

	SetPos(pos);

	CObjectBillboard::Update();

	if (m_nEffCtr >= 1)
	{
		//CEffect::Create(pos, GetRot(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 60, CEffect::TEX_000);
	
		m_nEffCtr = 0;
	}

	//��ʊO����


	//�▽����
	if (m_nLife <= 0)
	{
		CParticle::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f), D3DXVECTOR3(25.0f, 25.0f, 25.0f), CParticle::TYPE_EXPLODE);
		CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		Release();
		return;
	}

	//�G�Ƃ̓����蔻��
	if (CollisionCircle(pos))
	{//����������
		CScore *pScore = CGame::GetScore();
		
		if (pScore != nullptr)
		{
			pScore->CntValue(100);
		}

		return;
	}

	//�u���b�N�Ƃ̔���
	//if (CollisionRect())
	//{
	//	return;
	//}

	//���̃J�E���g�_�E��
	m_nLife--;

	//�J�E���^�[���Z
	m_nEffCtr++;
}

//============================
// 2D�e�̕`��
//============================
void CBullet::Draw(void)
{
	//�`��
	CObjectBillboard::Draw();
}

//============================
// �e�̐���
//============================
CBullet * CBullet::Create( D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const SIDE side, const int nDamage, const D3DXVECTOR3 size, const float fSpeed, const int nLife)
{
	CBullet *pBullet = nullptr;

	//�I�u�W�F�N�g����&������
	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		if (FAILED(pBullet->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			pBullet->m_nDamage = nDamage;

			pBullet->m_side = side;		//����

			pBullet->m_nLife = nLife;		//�̗͑��

			pBullet->SetSize(size);		//�T�C�Y�ݒ�

			CTexture *pTexture = CManager::GetInstance()->GetTexture();
			pBullet->SetIdxTexture(pTexture->Regist(FILE_PASS));

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			move.x = sinf(rot.y) * -fSpeed;
			move.z = cosf(rot.y) * -fSpeed;
			//pBullet->m_move.y = cosf(rot.y) * fSpeed;
			pBullet->SetMove(move);
		}
	}
	else
	{
		return nullptr;
	}

	return pBullet;
}

//============================
// �G�Ƃ̓����蔻��(�~��)
//============================
bool CBullet::CollisionCircle(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 size = GetSize();
	bool bCol = false;

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_ENEMY || type == CObject::TYPE_BOSS || type == CObject::TYPE_PLAYER)
				{//�G��������

					D3DXVECTOR3 Objpos = pObject->GetPos();

					D3DXVECTOR3 Objsize;

					type == CObject::TYPE_PLAYER ?
						Objsize = pObject->GetSize() :
						Objsize = pObject->GetMaxVtx();

					//3���g�������̔��肩��1���̉~�̔����
					float fSize0 = (size.x + size.z) * 0.5f;		//�A�C�e���̔��axz
					//float fSize1 = (size.x + size.y) * 0.5f;		//�A�C�e���̔��axy
					//float fSize2 = (size.z + size.y) * 0.5f;		//�A�C�e���̔��azy

					float fObjsize0 = (Objsize.x + Objsize.z) * 0.5f;		//�I�u�W�F�N�g�̔��axz
					//float fObjsize1 = (Objsize.x + Objsize.y) * 0.5f;		//�I�u�W�F�N�g�̔��axy
					//float fObjsize2 = (Objsize.z + Objsize.y) * 0.5f;		//�I�u�W�F�N�g�̔��azy

					float fColl0 = fSize0 + fObjsize0;		//�����蔻��͈�
					//float fColl1 = fSize1 + fObjsize1;		//�����蔻��͈�
					//float fColl2 = fSize2 + fObjsize2;		//�����蔻��͈�

					float fLength0 = hypotf((pos.x - Objpos.x), (pos.z - Objpos.z));					//2�_�Ԃ̒���xz
					//float fLength1 = hypotf((pos.x - Objpos.x), (pos.y - Objpos.y));		//2�_�Ԃ̒���xy
					//float fLength2 = hypotf((pos.z - Objpos.z), (pos.y - Objpos.y));		//2�_�Ԃ̒���zy

					//if (fLength0 <= fColl0 &&
					//	fLength1 <= fColl1 &&
					//	fLength2 <= fColl2)

					if (fLength0 <= fColl0 && pos.y <= 110.0f)
					{
						//�_�C�i�~�b�N�L���X�g
						if (type == CObject::TYPE_PLAYER && m_side != SIDE_PLAYER)
						{
							CPlayer *pPlayer = dynamic_cast<CPlayer*>(pObject);
							pPlayer->Damage(float(m_nDamage));
							bCol = true;
						}
						else if (type != CObject::TYPE_PLAYER && m_side != SIDE_ENEMY)
						{
							CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObject);
							pEnemy->Damage(m_nDamage);
							bCol = true;
						}

						if (bCol)
						{
							//��������
							CExplosion::Create(pos, D3DXVECTOR3(10.0f, 10.0f, 10.0f));

							//�e�I��
							Uninit();

							return bCol;
						}
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

	return bCol;
}

//============================
//�u���b�N�Ƃ̓����蔻��(��`)
//============================
bool CBullet::CollisionRect(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 posOld = pos - GetMove();

	D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Objsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool bCollision = false;			//�����蔻�肪���������ǂ���

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_BLOCK)
				{//�v���C���\��������
					Objpos = pObject->GetPos();
					Objsize = pObject->GetSize();

					if (Objpos.y + Objsize.y <= posOld.y - size.y
						&& Objpos.y + Objsize.y >= pos.y - size.y
						&& Objpos.x + Objsize.x >= pos.x - size.x + 0.1f
						&& Objpos.x - Objsize.x <= pos.x + size.x - 0.1f)
					{//�u���b�N��
						bCollision = true;
					}
					else if (Objpos.y - Objsize.y >= posOld.y + size.y
						&& Objpos.y - Objsize.y <= pos.y + size.y
						&& Objpos.x + Objsize.x >= pos.x - size.x + 0.1f
						&& Objpos.x - Objsize.x <= pos.x + size.x - 0.1f)
					{//�u���b�N��
						bCollision = true;
					}

					if (Objpos.x + Objsize.x <= posOld.x - size.x + 0.1f
						&& Objpos.x + Objsize.x >= pos.x - size.x + 0.1f
						&& Objpos.y + Objsize.y > pos.y - size.y
						&& Objpos.y - Objsize.y < pos.y + size.y)
					{//�u���b�N��
						bCollision = true;
					}
					else if (Objpos.x - Objsize.x >= posOld.x + size.x - 0.1f
						&& Objpos.x - Objsize.x <= pos.x + size.x - 0.1f
						&& Objpos.y + Objsize.y > pos.y - size.y
						&& Objpos.y - Objsize.y < pos.y + size.y)
					{//�u���b�N�E
						bCollision = true;
					}

					if (bCollision)
					{
						//��������
						CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

						Release();

						//�u���b�N�Ƀ_���[�W�H
						return bCollision;
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

	return bCollision;
}
