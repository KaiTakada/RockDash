//===============================================
//
// �p�[�e�B�N��(particle.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "particle.h"
#include "effect.h"
#include "debugproc.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^(�f�t�H)
//============================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	for (int nCntCrt = 0; nCntCrt < MAX_PARTICLE; nCntCrt++)
	{
		if (m_apEffect[nCntCrt] != nullptr)
		{
			m_apEffect[nCntCrt] = nullptr;
		}
	}

	m_nLife = 0;
}

//============================
// �f�X�g���N�^
//============================
CParticle::~CParticle()
{

}
//====================================
// ����������(�f�t�H)
//====================================
HRESULT CParticle::Init(void)
{
	for (int nCntCrt = 0; nCntCrt < MAX_PARTICLE; nCntCrt++)
	{
		if (m_apEffect[nCntCrt] == nullptr)
		{
			m_apEffect[nCntCrt] = CEffect::Create();		//���g����

			if (m_apEffect[nCntCrt] != nullptr)
			{
				m_apEffect[nCntCrt]->Init();
			}

			break;
		}
	}

	return S_OK;
}

//====================================
// ����������(�f�t�H)
//====================================
HRESULT CParticle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, D3DXVECTOR3 move, const D3DXVECTOR3 size, TYPE type)
{
	int nNum = 0;
	int nLife = 0;
	D3DXVECTOR3 vec = rot * 100.0f;
	D3DXVECTOR3 moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�^�C�v��
	switch (type)
	{
	case TYPE_EXPLODE:

		nNum = 30;
		nLife = 20;

		break;

	case TYPE_BOOST:

		nNum = 30;
		nLife = 40;

		if (vec.x < 1.0f && vec.x > -1.0f)
		{
			vec.x = 1.0f;
		}
		if (vec.y < 1.0f && vec.y > -1.0f)
		{
			vec.y = 1.0f;
		}
		if (vec.z < 1.0f && vec.z > -1.0f)
		{
			vec.z = 1.0f;
		}

		vec *= 100.0f;

		break;

	default:

		nNum = 10;
		nLife = 10;

		break;
	}

	for (int nCntCrt = 0; nCntCrt < nNum; nCntCrt++)
	{
		if (nCntCrt >= MAX_PARTICLE)
		{
			break;
		}

		//�^�C�v��
		switch (type)
		{
		case TYPE_EXPLODE:
			moveR.x = sinf((float)(rand() % 629 - 314) / 100.0f) * move.x;
			moveR.y = cosf((float)(rand() % 629 - 314) / 100.0f) * move.y;
			moveR.z = sinf((float)(rand() % 629 - 314) / 100.0f) * move.z;
			break;

		case TYPE_BOOST:
			moveR.x = sinf((float)(rand() % int(vec.x) - 79) / 100.0f) * move.x;
			moveR.y = cosf((float)(rand() % int(vec.y) - 79) / 100.0f) * move.y;
			moveR.z = sinf((float)(rand() % int(vec.z) - 79) / 100.0f) * move.z;
			break;

		default:
			moveR.x = sinf((float)(rand() % 629 - 314) / 100.0f) * move.x;
			moveR.y = cosf((float)(rand() % 629 - 314) / 100.0f) * move.y;
			moveR.z = sinf((float)(rand() % 629 - 314) / 100.0f) * move.z;
			break;
		}

		//CEffect::Create(pos, rot, moveR, size, nLife, CEffect::TEX_000);		//���g����
		m_apEffect[nCntCrt] = CEffect::Create(pos, rot, moveR, size, nLife, CEffect::TEX_000);		//���g����
	
		if (type == TYPE_BOOST)
		{
			m_apEffect[nCntCrt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	SetType(TYPE_PARTICLE);

	return S_OK;
}

//====================================
// ����������(�I�o��)
//====================================
HRESULT CParticle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	pos;
	rot;

	return S_OK;
}

//============================
// �I������
//============================
void CParticle::Uninit(void)
{
	for (int nCntCrt = 0; nCntCrt < MAX_PARTICLE; nCntCrt++)
	{
		if (m_apEffect[nCntCrt] != nullptr)
		{
			m_apEffect[nCntCrt] = nullptr;
		}
	}

	if (m_apEffect != nullptr)
	{
	}

	CObject::Release();
}

//============================
// �X�V����
//============================
void CParticle::Update(void)
{
	if (m_nLife <= 0)
	{
		Uninit();
	}
	else
	{
		m_nLife--;
	}
}

//============================
// �`�揈��
//============================
void CParticle::Draw(void)
{

}

//==========================
// ������
//==========================
CParticle *CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const D3DXVECTOR3 size, TYPE m_type)
{
	CParticle *pParticle = nullptr;

	pParticle = new CParticle;

	if (pParticle != nullptr)
	{
		pParticle->Init(pos,rot,move,size,m_type);
		pParticle->m_nLife = 1;
	}
	else
	{
		return nullptr;
	}

	return pParticle;
}

//============================
// �j��
//============================
void CParticle::Release(int nID)
{
	nID;
}

//============================
// �ʒu�ݒ�
//============================
void CParticle::SetPos(const D3DXVECTOR3 pos)
{
	pos;
}

//============================
// �����ݒ�
//============================
void CParticle::SetRot(const D3DXVECTOR3 rot)
{
	rot;
}

//============================
// �ʒu�擾
//============================
D3DXVECTOR3 CParticle::GetPos(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
// 2D�T�C�Y�擾
//============================
D3DXVECTOR3 CParticle::GetSize(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
