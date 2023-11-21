//===============================================
//
// �X�R�A(score.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "timer.h"
#include "score.h"
#include "object2D.h"
#include "texture.h"

//============================
// �}�N����`
//============================
#define MAX_TIME_SCORE_DIGIT (2)	//�X�R�A����
#define MAX_TIME_SCORE_DIGIT_LIMIT (60)	//�X�R�A�����̏㏸�l
#define TIME_COLON_PASS "data\\TEXTURE\\NUMBER\\colon.png"	//�R����.png

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^
//============================
CTimer::CTimer()
{
	for (int nCntCrt = 0; nCntCrt < MAX_TIME_SCORE; nCntCrt++)
	{
		if (m_apScore[nCntCrt] != nullptr)
		{
			m_apScore[nCntCrt] = nullptr;
		}

		if (m_apColon[nCntCrt] != nullptr && nCntCrt < MAX_TIME_SCORE - 1)
		{
			m_apColon[nCntCrt] = nullptr;
		}
	}

	m_nValue = 0;
	m_nSecond = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3();
	m_bStop = false;

	ZeroMemory(&m_time, sizeof(m_time));
}

//============================
// �f�X�g���N�^
//============================
CTimer::~CTimer()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CTimer::Init(void)
{
	SetType(TYPE_TIMER);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CTimer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	pos;
	rot;

	SetType(TYPE_TIMER);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CTimer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 posDif = pos;
	m_bStop = false;

	for (int nCntAll = 0; nCntAll < MAX_TIME_SCORE; nCntAll++)
	{
		if (m_apScore[nCntAll] == nullptr)
		{
			m_apScore[nCntAll] = CScore::Create(posDif, rot, size, 2);		//���g����

			posDif.x += (size.x * 2) * 2;		//����1���~2��(00)
		}

		if (m_apColon[nCntAll] == nullptr && nCntAll < MAX_TIME_SCORE - 1)
		{
			m_apColon[nCntAll] = CObject2D::Create(posDif, rot, size, CObject2D::UPDATE_TYPE_NONE);
		
			CTexture *pTex = CManager::GetInstance()->GetTexture();
			
			//�e�N�X�`���t�^
			m_apColon[nCntAll]->SetIdxTexture(pTex->Regist(TIME_COLON_PASS));

			posDif.x += (size.x * 2);		//����1���~1��(:)
		}
	}

	SetType(TYPE_TIMER);

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CTimer::Uninit(void)
{
	for (int nCntDel = 0; nCntDel < MAX_TIME_SCORE; nCntDel++)
	{
		if (m_apScore[nCntDel] != nullptr)
		{
			m_apScore[nCntDel]->Uninit();
			m_apScore[nCntDel] = nullptr;
		}
	
		if (m_apColon[nCntDel] != nullptr && nCntDel < MAX_TIME_SCORE - 1)
		{
			m_apColon[nCntDel]->Uninit();
			m_apColon[nCntDel] = nullptr;
		}
	}

	Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CTimer::Update(void)
{
	DWORD dwTimeNow = timeGetTime();
	DWORD dwTimeOld = timeGetTime();
}

//============================
// 2D�|���S���̕`�揈��
//============================
void CTimer::Draw(void)
{

}

//============================
// 2D�|���S���̐�������
//============================
CTimer * CTimer::Create(void)
{
	CTimer *pScore;

	//�I�u�W�F�N�g����
	pScore = new CTimer;

	//������
	pScore->Init();

	return pScore;
}

//============================
// 2D�|���S���̐�������
//============================
CTimer * CTimer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CTimer *pScore = nullptr;

	//�I�u�W�F�N�g����&������
	if (pScore == nullptr)
	{
		pScore = new CTimer;

		if (pScore != nullptr)
		{
			pScore->Init(pos, rot, size);
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	return pScore;
}

//============================
// �X�R�A�l�ݒ�
//============================
void CTimer::SetValue(int nValue)
{
	if (m_bStop != false)
	{//���łɒ�~����Ă����ꍇ
		return;
	}

	m_nValue = nValue;

	STime lTime =
	{
	0,
	0,
	nValue
	};

	SetTime(lTime);
}

//============================
// �X�R�A�l���Z
//============================
void CTimer::CntValue(int nValue)
{
	if (m_bStop != false)
	{//���łɒ�~����Ă����ꍇ
		return;
	}

	m_nValue += nValue;
	m_time.nMilliSecond += nValue;

	SetValue(m_nValue);
}

//============================
// �^�C���ݒ�
//============================
void CTimer::SetTime(STime time)
{
	if (m_bStop != false)
	{//���łɒ�~����Ă����ꍇ
		return;
	}

	m_time = time;
	STime lTime = time;

	//�e���̐������i�[
	int aTex[MAX_TIME_SCORE] = 
	{
		lTime.nMinute,
		lTime.nSecond,
		lTime.nMilliSecond,
	};

	//���l�̐ݒ�

	//�e�N�X�`�����W�̌v��
	for (int nCntScore = MAX_TIME_SCORE - 1; nCntScore > 0; nCntScore--)
	{
		int nCntNext = nCntScore - 1;
		aTex[nCntNext] = aTex[nCntScore] / MAX_TIME_SCORE_DIGIT_LIMIT;
		aTex[nCntScore] %= MAX_TIME_SCORE_DIGIT_LIMIT;
	}

	lTime.nMinute = aTex[0];
	lTime.nSecond = aTex[1];
	lTime.nMilliSecond = aTex[2];

	for (int nCntSet = 0; nCntSet < MAX_TIME_SCORE; nCntSet++)
	{
		m_apScore[nCntSet]->SetValue(aTex[nCntSet]);
	}
}

//============================
// �^�C�����Z
//============================
void CTimer::CntTime(STime time)
{
	if(m_bStop != false)
	{//���łɒ�~����Ă����ꍇ
		return;
	}

	//�I�y���[�^�[���g�p�������Z��
	m_time += time;

	SetTime(m_time);
}

//============================
// �ʒu�ݒ�
//============================
void CTimer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	//�X�R�A�Q�ɂ��^����
}

//============================
// �����ݒ�
//============================
void CTimer::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	//�X�R�A�Q�ɂ��^����
}

//============================
// ���Ԍ^�̉��Z���̃I�[�o�[���[�h[���Z]
//============================
CTimer::STime & CTimer::STime::operator+=(const STime &time)
{
	nMinute += time.nMinute;
	nSecond += time.nSecond;
	nMilliSecond += time.nMilliSecond;

	return *this;
}
