//==================================================
//
// �u�[�X�^�[(wp_boost.cpp) �p���FCWeapon
// Author : Kai Takada
//
//==================================================
#include "wp_boost.h"
#include "weapon.h"
#include "Xmodel.h"
#include "manager.h"
#include "bullet.h"

#include "sound.h"
#include "particle.h"

//=======================
// �}�N����`
//=======================
#define READ_SIZE (128)		//�Ǎ��|�C���^�T�C�Y

//=======================
// �ÓI�����o�ϐ��錾
//=======================

//=======================
// �R���X�g���N�^
//=======================
CBoost::CBoost(int nPriority) : CWeapon(nPriority)
{

}

//=======================
// �f�X�g���N�^
//=======================
CBoost::~CBoost()
{

}

//=======================
// ����������
//=======================
HRESULT CBoost::Init(void)
{
	CWeapon::Init();
	
	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// ����������
//=======================
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CWeapon::Init(pos, rot, CWeapon::WPNTYPE_BOOST);

	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// �I������
//=======================
void CBoost::Uninit(void)
{
	CWeapon::Uninit();
}

//=======================
// �X�V����
//=======================
void CBoost::Update(void)
{
	CWeapon::Update();
}

//=======================
// �`�揈��
//=======================
void CBoost::Draw(void)
{
	CWeapon::Draw();
}

//=======================
// �U������
//=======================
void CBoost::Attack(const D3DXVECTOR3 rot, const int nDamage)
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

	//�u�[�X�g�G�t�F�N�g
	CParticle::Create(pos, rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), CParticle::TYPE_BOOST);
}

//=======================
// ��������
//=======================
CBoost *CBoost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	CBoost *pWeapon = nullptr;

	//�I�u�W�F�N�g����&������
	pWeapon = new CBoost;

	if (pWeapon != nullptr)
	{
		if (FAILED(pWeapon->Init(pos, rot)))
		{
			return nullptr;
		}
		else
		{
			//���f���̊��蓖�Ă͐e�ňꊇ�ōs��
		}
	}
	else
	{
		return nullptr;
	}

	return pWeapon;
}
