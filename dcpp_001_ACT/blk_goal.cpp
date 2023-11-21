//==================================================
//
// �S�[������(blk_goal.cpp)
// Author : Kai Takada
//
//==================================================
#include "blk_goal.h"
#include "manager.h"
#include "fade.h"

//=======================
// �}�N����`
//=======================
#define GOAL_MODEL "data\\MODEL\\GOAL\\ring.x"						//�S�[�������O�̃��f���p�X

//=======================
// �o�C�i���t�@�C����
//=======================

//=======================
// �ÓI�����o�ϐ��錾
//=======================

//=======================
// �R���X�g���N�^
//=======================
CBlk_Goal::CBlk_Goal(int nPriority) : CBlock(nPriority)
{

}

//=======================
// �f�X�g���N�^
//=======================
CBlk_Goal::~CBlk_Goal()
{

}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlk_Goal::Init(void)
{
	CBlock::Init();

	D3DXVECTOR3 vtxMin = DEF_VEC3;
	D3DXVECTOR3 vtxMax = DEF_VEC3;

	SetType_Blk(CBlock::TYPE_GOAL);

	CXModel *pXmodel = CManager::GetInstance()->GetXModel();
	SetIdxModel(pXmodel->Regist(GOAL_MODEL, &vtxMin, &vtxMax));		//���f�����蓖��

	vtxMin = pXmodel->GetAddress(GetIdxModel())->vtxMin;
	vtxMax = pXmodel->GetAddress(GetIdxModel())->vtxMax;
	SetVtx(vtxMin, vtxMax);

	//90�x��]������
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	D3DXVECTOR3 vtxCom = vtxMin;
	vtxMin.x = vtxCom.z;
	vtxMin.z = vtxCom.x;

	vtxCom = vtxMax;

	vtxMax.x = vtxCom.z;
	vtxMax.z = vtxCom.x;
	SetVtx(vtxMin, vtxMax);

	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlk_Goal::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE_Blk type)
{
	CBlock::Init(pos, rot, type);

	D3DXVECTOR3 vtxMin = DEF_VEC3;
	D3DXVECTOR3 vtxMax = DEF_VEC3;

	SetType_Blk(type);

	CXModel *pXmodel = CManager::GetInstance()->GetXModel();
	SetIdxModel(pXmodel->Regist(GOAL_MODEL, &vtxMin, &vtxMax));		//���f�����蓖��

	vtxMin = pXmodel->GetAddress(GetIdxModel())->vtxMin;
	vtxMax = pXmodel->GetAddress(GetIdxModel())->vtxMax;
	SetVtx(vtxMin, vtxMax);

	//90�x��]������
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	D3DXVECTOR3 vtxCom = vtxMin;
	vtxMin.x = vtxCom.z;
	vtxMin.z = vtxCom.x;

	vtxCom = vtxMax;

	vtxMax.x = vtxCom.z;
	vtxMax.z = vtxCom.x;
	SetVtx(vtxMin, vtxMax);

	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏I������
//=======================
void CBlk_Goal::Uninit(void)
{
	CBlock::Uninit();
}

//=======================
//�u���b�N�̍X�V����
//=======================
void CBlk_Goal::Update(void)
{
	CBlock::Update();
}

//=======================
//�u���b�N�̕`�揈��
//=======================
void CBlk_Goal::Draw(void)
{
	CObjectX::Draw();
}

//=======================
//�u���b�N�̐ݒ菈��
//=======================
CBlk_Goal *CBlk_Goal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBlk_Goal *pGoal = nullptr;

	//�I�u�W�F�N�g����&������
	pGoal = new CBlk_Goal;

	if (pGoal != nullptr)
	{
		if (FAILED(pGoal->Init(pos, rot)))
		{
			return nullptr;
		}
		else
		{
			pGoal->SetType_Blk(CBlock::TYPE_GOAL);

			CXModel *pXmodel = CManager::GetInstance()->GetXModel();
			pGoal->SetIdxModel(pXmodel->Regist(GOAL_MODEL, &vtxMin, &vtxMax));		//���f�����蓖��
		}
	}
	else
	{
		return nullptr;
	}

	return pGoal;
}

//============================
//�u���b�N�̓����蔻��(����ŉ����߂�)
//============================
bool CBlk_Goal::CollisionRect(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 sizeMin = GetMinVtx();		//�ŏ��l
	D3DXVECTOR3 sizeMax = GetMaxVtx();		//�ő�l

	D3DXVECTOR3 posC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posOldC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sizeC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 moveC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����߂���

	bool Collision = false;			//�����蔻�肪���������ǂ���

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr) && Collision == false)
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

					if (sizeOldMaxC.x <= pos.x + sizeMin.x
						&& sizeMaxC.x > pos.x + sizeMin.x
						&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
						&& sizeMinC.z < pos.z + sizeMax.z + 0.1f
						&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
							&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
							|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N��
						Collision = true;
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
						Collision = true;
					}

					if (sizeOldMaxC.z <= pos.z + sizeMin.z
						&& sizeMaxC.z > pos.z + sizeMin.z
						&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
						&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
						&& ((sizeMaxC.y >= pos.y + sizeMin.y + 0.1f
							&& sizeMaxC.y <= pos.y + sizeMax.y - 0.1f)
							|| (sizeMinC.y >= pos.y + sizeMin.y + 0.1f
								&& sizeMinC.y <= pos.y + sizeMax.y - 0.1f)))
					{//�u���b�N�k
						Collision = true;
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
						Collision = true;
					}

					if (sizeOldMinC.y >= pos.y + sizeMax.y
						&& sizeMinC.y <= pos.y + sizeMax.y
						&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
						&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
						&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
						&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
					{//�u���b�N��
						Collision = true;
					}
					else if (sizeOldMaxC.y <= pos.y + sizeMin.y
						&& sizeMaxC.y >= pos.y + sizeMin.y
						&& sizeMaxC.x > pos.x + sizeMin.x + 0.1f
						&& sizeMinC.x < pos.x + sizeMax.x + 0.1f
						&& sizeMaxC.z > pos.z + sizeMin.z + 0.1f
						&& sizeMinC.z < pos.z + sizeMax.z + 0.1f)
					{//�u���b�N��
						Collision = true;
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

	if (Collision)
	{//�G��Ă�����
		//�^�C�����~���ۑ��B���U���g�J�ڏ����B
		CManager::GetInstance()->SetResult(CManager::RT_WIN);
	
		CFade *pFade = CScene::GetFade();

		if (CManager::GetInstance()->GetResult() != CManager::RT_NONE)
		{//���ʂ��m�肵����

			pFade->SetState(CScene::MODE_RESULT);
		}
	}

	return Collision;
}
