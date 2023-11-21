//===============================================
//
// �{�X�G(enemy_boss.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "enemy_boss.h"
#include "bullet.h"

//============================
// �}�N����`
//============================
#define NUM_ATTACK (1.0f)	//�U����
#define NUM_HP (10.0f)		//�̗�
#define NUM_SPEED (20.0f)	//�ړ���
#define BOSS_FILE "data\\MODEL\\ENEMY\\tank.x"		//boss���
#define NUM_COOL (120)	//�N�[���^�C��
#define NUM_BURST (60)	//burst�����ː�
#define NUM_TACKLE (30)	//tackle���t���[����
#define NUM_TACKLE_ADD (10.0f)	//tackle���X�s�[�h�����l
#define NUM_BURST_READY (60)	//burst�����t���[��

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^
//============================
CEnemy_Boss::CEnemy_Boss(int nPriority) : CEnemy(nPriority)
{
	m_AttackState = AS_NONE;
	m_nCoolTime = 0;
	m_bClear = true;
	m_nMoveCnt = 0;
}

//============================
// �f�X�g���N�^
//============================
CEnemy_Boss::~CEnemy_Boss()
{

}

//====================================
// ������(�f�t�H)
//====================================
HRESULT CEnemy_Boss::Init(void)
{
	//������
	CEnemy::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_BOSS);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CEnemy_Boss::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//������
	if(FAILED(CEnemy::Init(pos, rot)))
	{
		return E_FAIL;
	}

	//�^�C�v�ݒ�
	SetType(TYPE_BOSS);

	return S_OK;
}

//============================
// �I��
//============================
void CEnemy_Boss::Uninit(void)
{
	//�I��
	CEnemy::Uninit();
}

//============================
// �X�V
//============================
void CEnemy_Boss::Update(void)
{
	Param param = GetParam();
	float fRatio = param.fLife / param.fLifeMax;

	if (!GetMoveFrag())
	{//�������肶��Ȃ����

		if (fRatio <= 0.9)
		{
			SetMoveFrag(true);
			return;
		}
		else
		{
			return;
		}
	}

	Attack();

	if (m_bClear == true && m_nCoolTime <= 0)
	{//�s������&�N�[���_�E������

		//�����_���s���ݒ�
		int nSet = 0;

		fRatio = param.fLife / param.fLifeMax;

		if (fRatio <= 0.5)
		{//�̗͂������ɂȂ�ƃ^�b�N���ǉ�
			nSet = rand() % AS_MAX;
		}
		else if (fRatio <= 0.9)
		{//�̗͂������ɂȂ�ƃ^�b�N���ǉ�
			nSet = rand() % AS_MAX;
			
		}
		else
		{
			nSet = rand() % AS_TACKLE;
		}

#if _DEBUG
		SetAttack(CEnemy_Boss::ATACKSTATE(nSet));
#else
		SetAttack(CEnemy_Boss::ATACKSTATE(nSet));
#endif
	}
	else if (m_bClear == true && m_nCoolTime > 0)
	{//�s������&�N�[���_�E����
		m_nCoolTime--;
	}

	CEnemy::Update();
}

//============================
// �`��
//============================
void CEnemy_Boss::Draw(void)
{
	//�`��
	CEnemy::Draw();
}

//============================
// �G����
//============================
CEnemy_Boss * CEnemy_Boss::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CEnemy_Boss *pEnemy = nullptr;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�I�u�W�F�N�g����&������
	pEnemy = new CEnemy_Boss;

	if (pEnemy != nullptr)
	{
		pEnemy->Init(pos, rot);

		pEnemy->SetTypeE(ET_BOSS);
		pEnemy->InitialState(ET_BOSS);
		pEnemy->InitialMove();
		
		CXModel *pXmodel = CManager::GetInstance()->GetXModel();
		pEnemy->SetIdxModel(pXmodel->Regist(BOSS_FILE, &vtxMin, &vtxMax));		//���f���̊��蓖��

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
// �U���ݒ�
//============================
void CEnemy_Boss::SetAttack(CEnemy_Boss::ATACKSTATE state)
{
	m_AttackState = state;
	m_nMoveCnt = 0;
	m_bClear = false;

	switch (m_AttackState)
	{

	case CEnemy_Boss::AS_BURST:
	case CEnemy_Boss::AS_TACKLE:
		m_nCoolTime = NUM_COOL;
		break;

	default:
		m_nCoolTime = 0;
		m_bClear = true;
		break;
	}
}

//============================
// �U���ē�
//============================
void CEnemy_Boss::Attack()
{
	switch (m_AttackState)
	{
	case CEnemy_Boss::AS_STALK:

		StalkPlayer();
		m_bClear = true;

		break;

	case CEnemy_Boss::AS_BURST:

		m_bClear = Burst();

		break;

	case CEnemy_Boss::AS_TACKLE:

		m_bClear = Tackle();

		break;

	default:

		m_AttackState = AS_NONE;
		m_nCoolTime = 0;

		break;
	}

	m_nMoveCnt++;
}

//============================
// �e����
//============================
bool CEnemy_Boss::Burst()
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (m_nMoveCnt >= NUM_BURST_READY)
	{//����60f

		//�v���C���\�ւ̊p�x����NUM_BURST�̔��������炵��1�t���[���Ɉꔭ�����炵�đł�
		CBullet::Create(pos, rot, CBullet::SIDE_ENEMY, 2);
		rot.y += 0.01f;

		if (m_nMoveCnt >= NUM_BURST_READY + NUM_BURST)
		{
			//����������
			m_AttackState = AS_NONE;

			return true;
		}
	}
	else if (m_nMoveCnt == NUM_BURST_READY - 1)
	{//���ˑO

		rot.y -= 0.01f * NUM_BURST;
		SetRot(rot);
	}

	//�����łȂ��Ȃ�
	return false;
}

//============================
// �ːi
//============================
bool CEnemy_Boss::Tackle()
{
	Param param = GetParam();

	if (m_nMoveCnt >= NUM_BURST_READY)
	{//����60f

		//�����ړ�����

		//����
		param.fSpeed *= NUM_TACKLE_ADD;
		SetParam(param);

		StalkPlayer();

		//���ɖ߂�
		param.fSpeed *= (1 / NUM_TACKLE_ADD);
		SetParam(param);

		if (m_nMoveCnt >= NUM_BURST_READY + NUM_TACKLE)
		{
			//����������
			m_AttackState = AS_NONE;

			return true;
		}
	}
	else if (m_nMoveCnt == NUM_BURST_READY - 1)
	{//���ˑO

	}

	//�����łȂ��Ȃ�
	return false;
}
