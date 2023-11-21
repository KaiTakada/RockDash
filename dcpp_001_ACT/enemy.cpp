//===============================================
//
// �G(enemy.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "enemy.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "experience.h"
#include "state_life.h"		//��ԊǗ�
#include "score.h"

//============================
// �}�N����`
//============================
#define NUM_ATTACK (1.0f)	//�U����
#define NUM_HP (10.0f)		//�̗�
#define NUM_SPEED (20.0f)	//�ړ���
#define ENEMY_FILE "data\\SET\\ENEMY\\parameter.txt"		//���[�V�����t�@�C���p�X

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �G�̎�ރ��f��
//============================
const char *c_apFilenameEnemy[] =
{
	"data\\MODEL\\ENEMY\\probe.x",		//none�T���@
	"data\\MODEL\\ENEMY\\bike.x",		//speed�o�C�N
	"data\\MODEL\\ENEMY\\waller.x",		//hp�o�b�^��
	"data\\MODEL\\ENEMY\\tank.x",		//boss���
};

//============================
// �R���X�g���N�^
//============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_param.fAttack = 0.0f;
	m_param.fLife = 0.0f;
	m_param.fLifeMax = 0.0f;
	m_param.fSpeed = 0.0f;
	m_pStateLife = nullptr;

	m_bMove = false;
}

//============================
// �f�X�g���N�^
//============================
CEnemy::~CEnemy()
{

}

//====================================
// ������(�f�t�H)
//====================================
HRESULT CEnemy::Init(void)
{
	//������
	CObjectX::Init();

	//��Ԃ̐���
	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Uninit();
		m_pStateLife = nullptr;
	}

	m_pStateLife = CState_Life::Create();

	//�^�C�v�ݒ�
	SetType(TYPE_ENEMY);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CEnemy::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//������
	if(FAILED(CObjectX::Init(pos, rot)))
	{
		return E_FAIL;
	}

	//�^�C�v�ݒ�
	SetType(TYPE_ENEMY);

	//��Ԃ̐���
	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Uninit();
		m_pStateLife = nullptr;
	}

	m_pStateLife = CState_Life::Create();

	return S_OK;
}

//============================
// �I��
//============================
void CEnemy::Uninit(void)
{
	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Uninit();
		m_pStateLife = nullptr;
	}

	//�I��
	CObjectX::Uninit();
}

//============================
// �X�V
//============================
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	pos += m_move;
	SetPos(pos);

	if (m_bMove == false)
	{//������ۂœˌ�
		StalkPlayer();
	}
	else if(m_type == ET_BOSS)
	{
		MoveBoss();
	}

	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Update();
	}

	CollisionCircle(pos);
	//CollisionRect();

	CObjectX::Update();
}

//============================
// �`��
//============================
void CEnemy::Draw(void)
{
	D3DXMATERIAL m_DefMat;				//�f�t�H���g�}�e���A���f�[�^�ւ̃|�C���^

	if (m_pStateLife != nullptr)
	{
		if (m_pStateLife->Get() == CState_Life::STATE_DAMAGE)
		{
			m_DefMat = m_pStateLife->GetMat();
			
			CObjectX::Draw(m_DefMat.MatD3D);
		}
		else
		{
			CObjectX::Draw();
		}
	}
}

//============================
// �G����
//============================
CEnemy * CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type)
{
	CEnemy *pEnemy = nullptr;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�I�u�W�F�N�g����&������
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		pEnemy->Init(pos, rot);

		pEnemy->m_type = type;
		pEnemy->InitialState(type);
		pEnemy->InitialMove();

		CXModel *pXmodel = CManager::GetInstance()->GetXModel();
		pEnemy->SetIdxModel(pXmodel->Regist(c_apFilenameEnemy[type], &vtxMin, &vtxMax));		//���f���̊��蓖��

		vtxMin = pXmodel->GetAddress(pEnemy->GetIdxModel())->vtxMin;
		vtxMax = pXmodel->GetAddress(pEnemy->GetIdxModel())->vtxMax;
		pEnemy->SetVtx(vtxMin, vtxMax);
	}
	else
	{
		return nullptr;
	}

	return pEnemy;
}

//============================
// �_���[�W����
//============================
void CEnemy::Damage(int nDamege)
{
	if (m_pStateLife != nullptr)
	{
		if (m_pStateLife->Get() != CState_Life::STATE_NORMAL)
		{//�_���[�W���󂯂��Ȃ���ԂȂ�
			return;
		}
	}

	m_param.fLife -= nDamege;

	m_pStateLife->Set(CState_Life::STATE_DAMAGE, 3);

	if (m_param.fLife <= 0)
	{
		CScore *pScore = CGame::GetScore();

		if (pScore == nullptr)
		{
			SetDeath(true);
			return;
		}

		if (m_type == ET_BOSS)
		{
			pScore->CntValue(100000);

			CManager::GetInstance()->SetResult(CManager::RT_WIN);
			SetDeath(true);
		}
		else
		{
			pScore->CntValue(100);
			
			CExperience::Create(GetPos());
			SetDeath(true);
		}
	}
}

//============================
// �v���C���[��ǂ������鏈��
//============================
void CEnemy::StalkPlayer()
{
	CPlayer *pPlayer;

	if ((pPlayer = CGame::GetPlayer()) == nullptr)
	{
		return;
	}

	D3DXVECTOR3 posP = pPlayer->GetPos();

	D3DXVECTOR3 vecDiff = D3DXVECTOR3(posP.x - GetPos().x,
		0.0f,
		posP.z - GetPos().z);

	//�����C��
	D3DXVECTOR3 rot = GetRot();

	rot.y = atan2f(vecDiff.x, vecDiff.z) + D3DX_PI;

	SetRot(rot);

	D3DXVec3Normalize(&vecDiff, &vecDiff);		//�x�N�g���𐳋K������(1.0f�ɂ���)

	//�ŗL�̃X�s�[�h���悹��
	vecDiff.x *= m_param.fSpeed;
	vecDiff.z *= m_param.fSpeed;

	SetMove(vecDiff);
}

//============================
// �v���C���[�Ƃ̓����蔻��(��`)
//============================
bool CEnemy::CollisionRect(void)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����߂���
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetMaxVtx();
	D3DXVECTOR3 sizeMax = GetMaxVtx();
	D3DXVECTOR3 sizeMin = GetMinVtx();
	D3DXVECTOR3 posOld = pos - m_move;

	D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ObjposOld = Objpos;
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

				if (type == CObject::TYPE_PLAYER)
				{//�v���C���\��������
					Objpos = pObject->GetPos();
					ObjposOld = pObject->GetPosOld();
					Objsize = pObject->GetSize();

					if (ObjposOld.z + Objsize.z <= pos.z + sizeMin.z
						&& Objpos.z + Objsize.z >= pos.z + sizeMin.z
						&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
						&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
						&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
							&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
							|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N�k
						move.z = (pos.z + sizeMin.z) - (Objpos.z + Objsize.z) - 0.1f;
						bCollision = true;
					}
					else if (ObjposOld.z - Objsize.z >= pos.z + sizeMax.z
						&& Objpos.z - Objsize.z <= pos.z + sizeMax.z
						&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
						&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
						&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
							&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
							|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N��
						move.z = (pos.z + sizeMax.z) - (Objpos.z - Objsize.z) + 0.1f;
						bCollision = true;
					}

					if (ObjposOld.x - Objsize.x >= pos.x + sizeMax.x
						&& Objpos.x - Objsize.x <= pos.x + sizeMax.x
						&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
						&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
						&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
							&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
							|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N��
						move.x = (pos.x + sizeMax.x) - (Objpos.x - Objsize.x) + 0.1f;
						bCollision = true;
					}
					else if (ObjposOld.x + Objsize.x <= pos.x + sizeMin.x
						&& Objpos.x + Objsize.x > pos.x + sizeMin.x
						&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
						&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
						&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
							&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
							|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N��
						move.x = (pos.x + sizeMin.x) - (Objpos.x + Objsize.x) - 0.1f;
						bCollision = true;
					}

					if (ObjposOld.y - Objsize.y >= pos.y + sizeMax.y
						&& Objpos.y - Objsize.y <= pos.y + sizeMax.y
						&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
						&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
						&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
						&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
					{//�u���b�N��
						D3DXVECTOR3 Objmove = pObject->GetMove();
						pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

						move.y = (pos.y + sizeMax.y) - (Objpos.y - Objsize.y) + 0.1f;
						pObject->SetJump(false);

						bCollision = true;
					}
					else if (ObjposOld.y + Objsize.y <= pos.y + sizeMin.y
						&& Objpos.y + Objsize.y >= pos.y + sizeMin.y
						&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
						&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
						&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
						&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
					{//�u���b�N��
						D3DXVECTOR3 Objmove = pObject->GetMove();
						pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

						move.y = (pos.y + sizeMin.y) - (Objpos.y + Objsize.y) - 0.1f;
						bCollision = true;
					}

					if (bCollision)
					{
						pObject->SetPos(Objpos + move);
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

//============================
// �G�Ƃ̓����蔻��(�~)
//============================
bool CEnemy::CollisionCircle(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 size = GetMaxVtx();

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_PLAYER)
				{//�G��������

					D3DXVECTOR3 Objpos = pObject->GetPos();
					D3DXVECTOR3 Objsize = pObject->GetMaxVtx();

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
						//�_�C�i�~�b�N�L���X�g
						//CPlayer *pPlayer = dynamic_cast<CPlayer*>(pObj);
						CPlayer *pPlayer = CGame::GetPlayer();

						//�G�I��
						if (pPlayer != nullptr)
						{
							pPlayer->Damage(m_param.fAttack);
						}

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

//============================
// �����X�e�U��
//============================
void CEnemy::InitialState(CEnemy::TYPE type)
{
	m_param.fAttack = NUM_ATTACK;
	m_param.fLife = NUM_HP;
	m_param.fLifeMax = NUM_HP;
	m_param.fSpeed = NUM_SPEED;

	char *pComp = new char[256];
	FILE *pFile;

	pFile = fopen(ENEMY_FILE, "r");

	if (pFile != nullptr)
	{
		int nCnt = 0;

		while (true)
		{
			fscanf(pFile, "%s", pComp);

			if (nCnt >= CEnemy::ET_MAX)
			{//�z��I�[�o�[
				break;
			}

			if (strncmp(pComp, "#", 1) == 0)
			{// ����̂��ƃR�����g
				fgets(pComp, 256, pFile);
				continue;
			}
			else if (strcmp(pComp, "SET_PARAM") == 0)
			{
				if (nCnt != type)
				{//
					nCnt++;
					continue;
				}
				
				nCnt++;

				while (true)
				{
					fscanf(pFile, "%s", pComp);

					if (strcmp(pComp, "END_PARAM") == 0)
					{
						break;
					}
					else if (strcmp(pComp, "LIFE") == 0)
					{
						fscanf(pFile, "%s", pComp);
						fscanf(pFile, "%f", &m_param.fLife);
						m_param.fLifeMax = m_param.fLife;
						continue;
					}
					else if (strcmp(pComp, "SPEED") == 0)
					{
						fscanf(pFile, "%s", pComp);
						fscanf(pFile, "%f", &m_param.fSpeed);
						continue;
					}
					else if (strcmp(pComp, "ATTACK") == 0)
					{
						fscanf(pFile, "%s", pComp);
						fscanf(pFile, "%f", &m_param.fAttack);
						continue;
					}
				}
			}
		}

		fclose(pFile);
	}

	delete[] pComp;

	//switch (type)
	//{
	//case CEnemy::ET_NONE:
	//	break;
	//
	//case CEnemy::ET_SPEED:
	//	m_param.fSpeed *= 2;
	//	break;
	//
	//case CEnemy::ET_HP:
	//	m_param.fLife *= 2;
	//	m_param.fLifeMax *= 2;
	//	break;
	//
	//case CEnemy::ET_BOSS:
	//	m_param.fLife *= 5;
	//	m_param.fLifeMax *= 5;
	//	m_param.fSpeed *= 0.1f;
	//	break;
	//
	//case CEnemy::ET_MAX:
	//	break;
	//
	//default:
	//	break;
	//}
}

//============================
// �^�C�v�ɉ������s���֐��ē�
//============================
void CEnemy::InitialMove()
{
	switch (m_type)
	{
	case CEnemy::ET_NONE:
		break;

	case CEnemy::ET_SPEED:
		MoveSpeed();
		break;

	case CEnemy::ET_HP:
		break;

	case CEnemy::ET_BOSS:
		MoveBoss();
		break;

	case CEnemy::ET_MAX:
		break;

	default:
		break;
	}
}

//============================
// �^�C�v�ɉ������s���֐��ē�
//============================
void CEnemy::MoveSpeed()
{
	CPlayer *pPlayer;

	if ((pPlayer = CGame::GetPlayer()) == nullptr)
	{
		return;
	}

	D3DXVECTOR3 posP = pPlayer->GetPos();

	D3DXVECTOR3 vecDiff = D3DXVECTOR3(posP.x - GetPos().x,
		0.0f,
		posP.z - GetPos().z);

	//�����C��
	D3DXVECTOR3 rot = GetRot();

	rot.y = atan2f(vecDiff.x, vecDiff.z) + D3DX_PI;

	SetRot(rot);

	D3DXVec3Normalize(&vecDiff, &vecDiff);		//�x�N�g���𐳋K������(1.0f�ɂ���)

	//�ŗL�̃X�s�[�h���悹��
	vecDiff.x *= m_param.fSpeed;
	vecDiff.z *= m_param.fSpeed;

	SetMove(vecDiff);

	m_bMove = true;
}

//============================
// �^�C�v�ɉ������s���֐��ē�
//============================
void CEnemy::MoveBoss()
{
	//�N��������

	//�N�[���^�C���ōU��

	//�t�F�[�Y�ōU�����e�؂�ւ����͒ǉ�

	if (m_bMove == false)
	{
		return;
	}

	StalkPlayer();
}
