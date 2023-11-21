//==================================================
//
// ���폈��(weapon.cpp) �p�� : Parts
// Author : Kai Takada
//
//==================================================
#include "weapon.h"
#include "Xmodel.h"
#include "manager.h"
#include "bullet.h"
#include "sound.h"

//=======================
// �}�N����`
//=======================
#define MUZZLE_FILE "data\\MODEL\\WEAPON\\muzzle.txt"		//�e���ʒu���
#define READ_SIZE (128)		//�Ǎ��|�C���^�T�C�Y

//=======================
// �o�C�i���t�@�C����
//=======================
const char *c_apFileWeapon[CWeapon::TYPE_MAX] =
{
	"data\\MODEL\\WEAPON\\nife.x",			//�i�C�t
	"data\\MODEL\\WEAPON\\revolver.x",		//���{���o�[
	"data\\MODEL\\WEAPON\\ak.x",			//���C�t��
	"data\\MODEL\\WEAPON\\boost.x",			//�u�[�X�g
};

//=======================
// �ÓI�����o�ϐ��錾
//=======================

//=======================
// �R���X�g���N�^
//=======================
CWeapon::CWeapon(int nPriority) : CParts(nPriority)
{
	m_type = WPNTYPE_REVOLVER;
	m_muzzlePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCooltime = 0;
	m_nCooltimeMin = 0;
}

//=======================
// �f�X�g���N�^
//=======================
CWeapon::~CWeapon()
{

}

//=======================
// ����������
//=======================
HRESULT CWeapon::Init(void)
{
	m_nCooltimeMin = 0;
	m_type = WPNTYPE_REVOLVER;

	CParts::Init();
	
	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// ����������
//=======================
HRESULT CWeapon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const WPNTYPE type)
{
	m_nCooltimeMin = 0;
	m_type = type;

	CParts::Init(pos, rot);

	CXModel *pXmodel = CManager::GetInstance()->GetXModel();
	SetIdxModel(pXmodel->Regist(c_apFileWeapon[type]));		//���f���̊��蓖��

	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// �I������
//=======================
void CWeapon::Uninit(void)
{
	CParts::Uninit();
}

//=======================
// �X�V����
//=======================
void CWeapon::Update(void)
{
	if (m_nCooltime > 0)
	{
		m_nCooltime--;
	}

	CParts::Update();
}

//=======================
// �`�揈��
//=======================
void CWeapon::Draw(void)
{
	CParts::Draw();
}

//=======================
// �U������
//=======================
void CWeapon::Attack(const D3DXVECTOR3 rot, const int nDamage)
{
	D3DXMATRIX mtxworld = GetMtxWorld();
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 mtxrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos.x = mtxworld._41;
	pos.y = mtxworld._42;
	pos.z = mtxworld._43;
	
	mtxrot.x = mtxworld._11 * mtxworld._21 * mtxworld._31;
	mtxrot.y = mtxworld._12 * mtxworld._22 * mtxworld._32;
	mtxrot.z = mtxworld._13 * mtxworld._23 * mtxworld._33;

	D3DXVECTOR3 muzzlePos;
	muzzlePos.x = mtxrot.x * m_muzzlePos.x;
	muzzlePos.y = mtxrot.y * m_muzzlePos.y;
	muzzlePos.z = mtxrot.z * m_muzzlePos.z;

	//�����ɉ������e���̈ʒu��file����擾���A�������甭�˂���
	if (m_nCooltime > 0)
	{
		return;
	}

	switch (m_type)
	{
	case WPNTYPE_NIFE:
		break;

	case WPNTYPE_REVOLVER:
		m_nCooltime = 30 - m_nCooltimeMin;
		CBullet::Create(pos + muzzlePos, rot + GetRot(), CBullet::SIDE_PLAYER, nDamage);
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ONFIRE);
		break;

	case WPNTYPE_AK:
		m_nCooltime = 15 - m_nCooltimeMin;
		CBullet::Create(pos + muzzlePos, rot + GetRot(), CBullet::SIDE_PLAYER, nDamage);
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ONFIRE);
		break;

	default:
		m_nCooltime = 5 - m_nCooltimeMin;
		CBullet::Create(muzzlePos, rot, CBullet::SIDE_PLAYER, nDamage);
		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ONFIRE);
		break;
	}

	if (m_nCooltime < 0)
	{//0�����ɂ͂Ȃ�Ȃ�
		m_nCooltime = 0;
	}
}

//=======================
// ��������
//=======================
CWeapon *CWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, WPNTYPE type)
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	CWeapon *pWeapon = nullptr;

	//�I�u�W�F�N�g����&������
	pWeapon = new CWeapon;

	if (pWeapon != nullptr)
	{
		if (FAILED(pWeapon->Init(pos, rot, type)))
		{
			return nullptr;
		}
		else
		{
			pWeapon->ReadMuzzleFile(type);

			CXModel *pXmodel = CManager::GetInstance()->GetXModel();
			pWeapon->SetIdxModel(pXmodel->Regist(c_apFileWeapon[type], &vtxMin, &vtxMax));		//���f���̊��蓖��
		}
	}
	else
	{
		return nullptr;
	}

	return pWeapon;
}

//=======================
// �^�C�v�ݒ�
//=======================
void CWeapon::SetWpnType(CWeapon::WPNTYPE type)
{
	CXModel *pXmodel = CManager::GetInstance()->GetXModel();
	SetIdxModel(pXmodel->Regist(c_apFileWeapon[type]));		//���f���̊��蓖��
	m_type = type;

	ReadMuzzleFile(type);
}

//============================
// �t�@�C���ǂݍ���
//============================
void CWeapon::ReadMuzzleFile(WPNTYPE type)
{
	char *pComp = new char[128];				//�ǂݍ��ޔ�
	char *pNum = new char[2];

	//����̃^�C�v�̐��l�𕶎��ɕϊ�
	snprintf(pNum, 2, "%d", type);

	FILE *pFile;

	pFile = fopen(MUZZLE_FILE, "r");

	if (pFile != nullptr)
	{//�t�@�C���Ǎ��ɐ��������ꍇ
		do
		{
			fscanf(pFile, "%s", pComp);

			if (strncmp(pComp, "#", 1) == 0)
			{// ����̂��ƃR�����g
				fgets(pComp, READ_SIZE, pFile);
				continue;
			}
			else if (strncmp(pComp, pNum, 2) == 0)
			{
				fscanf(pFile, "%f %f %f", &m_muzzlePos.x, &m_muzzlePos.y, &m_muzzlePos.z);

				break;
			}

		} while (strcmp(pComp, "END_SCRIPT") != 0);

		fclose(pFile);
	}

	delete[] pComp;
	delete[] pNum;
}


//============================
//�N�[���^�C���t�@�C���Ǎ�
//============================
void CWeapon::ReadCooltime(WPNTYPE type)
{
	char *pComp = new char[128];				//�ǂݍ��ޔ�
	char *pNum = new char[2];

	//����̃^�C�v�̐��l�𕶎��ɕϊ�
	snprintf(pNum, 2, "%d", type);

	FILE *pFile;

	pFile = fopen(MUZZLE_FILE, "r");

	if (pFile != nullptr)
	{//�t�@�C���Ǎ��ɐ��������ꍇ
		do
		{
			fscanf(pFile, "%s", pComp);

			if (strncmp(pComp, "#", 1) == 0)
			{// ����̂��ƃR�����g
				fgets(pComp, READ_SIZE, pFile);
				continue;
			}
			else if (strncmp(pComp, pNum, 2) == 0)
			{
				fscanf(pFile, "%d", &m_nCooltime);

				break;
			}

		} while (strcmp(pComp, "END_SCRIPT") != 0);

		fclose(pFile);
	}

	delete[] pComp;
	delete[] pNum;
}
