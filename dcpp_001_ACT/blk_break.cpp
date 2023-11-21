//==================================================
//
// �S�[������(blk_goal.cpp)
// Author : Kai Takada
//
//==================================================
#include "blk_break.h"
#include "manager.h"
#include "fade.h"

#include "game.h"
#include "player.h"
#include "motion.h"

//=======================
// �}�N����`
//=======================
#define GOAL_MODEL "data\\MODEL\\BLOCK\\brick_break.x"						//�S�[�������O�̃��f���p�X

//=======================
// �o�C�i���t�@�C����
//=======================

//=======================
// �ÓI�����o�ϐ��錾
//=======================

//=======================
// �R���X�g���N�^
//=======================
CBlk_Break::CBlk_Break(int nPriority) : CBlock(nPriority)
{

}

//=======================
// �f�X�g���N�^
//=======================
CBlk_Break::~CBlk_Break()
{

}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlk_Break::Init(void)
{
	CBlock::Init();
	
	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlk_Break::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE_Blk type)
{
	CBlock::Init(pos, rot, type);

	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏I������
//=======================
void CBlk_Break::Uninit(void)
{
	CBlock::Uninit();
}

//=======================
//�u���b�N�̍X�V����
//=======================
void CBlk_Break::Update(void)
{
	CBlock::Update();
}

//=======================
//�u���b�N�̕`�揈��
//=======================
void CBlk_Break::Draw(void)
{
	CObjectX::Draw();
}

//=======================
//�u���b�N�̐ݒ菈��
//=======================
CBlk_Break *CBlk_Break::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBlk_Break *pBreak = nullptr;

	//�I�u�W�F�N�g����&������
	pBreak = new CBlk_Break;

	if (pBreak != nullptr)
	{
		if (FAILED(pBreak->Init(pos, rot)))
		{
			return nullptr;
		}
		else
		{
			pBreak->SetType_Blk(CBlock::TYPE_BREAK);

			CXModel *pXmodel = CManager::GetInstance()->GetXModel();
			pBreak->SetIdxModel(pXmodel->Regist(GOAL_MODEL, &vtxMin, &vtxMax));		//���f�����蓖��
		
			vtxMin = pXmodel->GetAddress(pBreak->GetIdxModel())->vtxMin;
			vtxMax = pXmodel->GetAddress(pBreak->GetIdxModel())->vtxMax;
			pBreak->SetVtx(vtxMin, vtxMax);
		}
	}
	else
	{
		return nullptr;
	}

	return pBreak;
}

//============================
//�u���b�N�̓����蔻��(����ŉ����߂�or�󂳂��)
//============================
bool CBlk_Break::CollisionRect(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 sizeMin = GetMinVtx();		//�ŏ��l
	D3DXVECTOR3 sizeMax = GetMaxVtx();		//�ő�l

	D3DXVECTOR3 posC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posOldC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sizeC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����߂���

	bool bLand = false;			//���n�������ǂ���
	bool bCollision = false;			//�����蔻�肪���������ǂ���

										//x
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
					posC = pObject->GetPos();
					posOldC = pObject->GetPosOld();
					sizeC = pObject->GetSize();
					moveC = pObject->GetMove();

					D3DXVECTOR3 sizeOldMinC = D3DXVECTOR3(posOldC.x - sizeC.x, posOldC.y, posOldC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeOldMaxC = D3DXVECTOR3(posOldC.x + sizeC.x, posOldC.y + (sizeC.y * 2), posOldC.z + sizeC.z);		//�L�����ő�l

					D3DXVECTOR3 sizeMinC = D3DXVECTOR3(posC.x - sizeC.x, posC.y, posC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeMaxC = D3DXVECTOR3(posC.x + sizeC.x, posC.y + (sizeC.y * 2), posC.z + sizeC.z);		//�L�����ő�l

					if (pObject->GetJump() == false)
					{
						if (sizeOldMaxC.x <= pos.x + sizeMin.x
							&& sizeMaxC.x > pos.x + sizeMin.x
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMin.x) - (sizeMaxC.x) - 0.1f;
							bCollision = true;
						}
						else if (sizeOldMinC.x >= pos.x + sizeMax.x
							&& sizeMinC.x <= pos.x + sizeMax.x
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMax.x) - (sizeMinC.x) + 0.1f;
							bCollision = true;
						}
					}
					else
					{
						if (sizeOldMaxC.x <= pos.x + sizeMin.x
							&& sizeMaxC.x > pos.x + sizeMin.x
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMin.x) - (sizeMaxC.x) - 0.1f;
							bCollision = true;
						}
						else if (sizeOldMinC.x >= pos.x + sizeMax.x
							&& sizeMinC.x <= pos.x + sizeMax.x
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMax.x) - (sizeMinC.x) + 0.1f;
							bCollision = true;
						}
					}
				}

				if (bCollision)
				{
					pObject->SetPos(posC + move);
					bCollision = false;		//���Z�b�g����

					//�X���C�f�B���O��
					CPlayer *pPlayer = CGame::GetPlayer();

					if (pPlayer != nullptr)
					{
						CMotion *pMotion = pPlayer->GetMotion();
						if (pMotion != nullptr)
						{
							if (pMotion->GetType() == CPlayer::MOTIONTYPE_SLIDING)
							{
								//this�̎��S�t���O�𗧂Ă�
								SetDeath(true);
							}
						}
					}

					break;
				}

				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	//y
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
					posC = pObject->GetPos();
					posOldC = pObject->GetPosOld();
					sizeC = pObject->GetSize();
					moveC = pObject->GetMove();

					D3DXVECTOR3 sizeOldMinC = D3DXVECTOR3(posOldC.x - sizeC.x, posOldC.y, posOldC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeOldMaxC = D3DXVECTOR3(posOldC.x + sizeC.x, posOldC.y + (sizeC.y * 2), posOldC.z + sizeC.z);		//�L�����ő�l

					D3DXVECTOR3 sizeMinC = D3DXVECTOR3(posC.x - sizeC.x, posC.y, posC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeMaxC = D3DXVECTOR3(posC.x + sizeC.x, posC.y + (sizeC.y * 2), posC.z + sizeC.z);		//�L�����ő�l

					if (pObject->GetJump() == false)
					{
						if (sizeOldMinC.y >= pos.y + sizeMax.y
							&& sizeMinC.y <= pos.y + sizeMax.y
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMax.y) - (sizeMinC.y) + 0.1f;
							pObject->SetJump(false);
							pObject->SetBoost(false);
							bCollision = true;
							bLand = true;
						}
						else if (sizeOldMaxC.y <= pos.y + sizeMin.y
							&& sizeMaxC.y >= pos.y + sizeMin.y
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMin.y) - (sizeMaxC.y) - 0.1f;
							bCollision = true;
						}
					}
					else
					{
						if (sizeOldMinC.y >= pos.y + sizeMax.y
							&& sizeMinC.y <= pos.y + sizeMax.y
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMax.y) - (sizeMinC.y) + 0.1f;
							pObject->SetJump(false);
							pObject->SetBoost(false);
							bCollision = true;
							bLand = true;
						}
						else if (sizeOldMaxC.y <= pos.y + sizeMin.y
							&& sizeMaxC.y >= pos.y + sizeMin.y
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
							&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMin.y) - (sizeMaxC.y) - 0.1f;
							bCollision = true;
						}
					}
				}

				if (bCollision)
				{
					pObject->SetPos(posC + move);
					bCollision = false;
					break;
				}

				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	//z
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
					posC = pObject->GetPos();
					posOldC = pObject->GetPosOld();
					sizeC = pObject->GetSize();
					moveC = pObject->GetMove();

					D3DXVECTOR3 sizeOldMinC = D3DXVECTOR3(posOldC.x - sizeC.x, posOldC.y, posOldC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeOldMaxC = D3DXVECTOR3(posOldC.x + sizeC.x, posOldC.y + (sizeC.y * 2), posOldC.z + sizeC.z);		//�L�����ő�l

					D3DXVECTOR3 sizeMinC = D3DXVECTOR3(posC.x - sizeC.x, posC.y, posC.z - sizeC.z);		//�L�����ŏ��l
					D3DXVECTOR3 sizeMaxC = D3DXVECTOR3(posC.x + sizeC.x, posC.y + (sizeC.y * 2), posC.z + sizeC.z);		//�L�����ő�l

					if (pObject->GetJump() == false)
					{
						if (sizeOldMaxC.z <= pos.z + sizeMin.z
							&& sizeMaxC.z > pos.z + sizeMin.z
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N�k
							move.z = (pos.z + sizeMin.z) - (sizeMaxC.z) - 0.1f;
							bCollision = true;
						}
						else if (sizeOldMinC.z >= pos.z + sizeMax.z
							&& sizeMinC.z <= pos.z + sizeMax.z
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.z = (pos.z + sizeMax.z) - (sizeMinC.z) + 0.1f;
							bCollision = true;
						}
					}
					else
					{
						if (sizeOldMaxC.z <= pos.z + sizeMin.z
							&& sizeMaxC.z > pos.z + sizeMin.z
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N�k
							move.z = (pos.z + sizeMin.z) - (sizeMaxC.z) - 0.1f;
							bCollision = true;
						}
						else if (sizeOldMinC.z >= pos.z + sizeMax.z
							&& sizeMinC.z <= pos.z + sizeMax.z
							&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
							&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
							&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
								|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
									&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.z = (pos.z + sizeMax.z) - (sizeMinC.z) + 0.1f;
							bCollision = true;
						}
					}
				}

				if (bCollision)
				{
					pObject->SetPos(posC + move);
					bCollision = false;
					break;
				}

				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	return bLand;
}
