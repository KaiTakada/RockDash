//===============================================
//
// �X�R�A(score.cpp)
// Author ���c ����
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "score.h"
#include "number.h"

//============================
// �}�N����`
//============================

//============================
// �ÓI�����o�ϐ��錾
//============================

//============================
// �R���X�g���N�^
//============================
CScore::CScore()
{
	for (int nCntCrt = 0; nCntCrt < MAX_SCORE; nCntCrt++)
	{
		if (m_apNumber[nCntCrt] != nullptr)
		{
			m_apNumber[nCntCrt] = nullptr;
		}
	}

	m_nValue = 0;
	m_nNum = 0;
}

//============================
// �f�X�g���N�^
//============================
CScore::~CScore()
{

}

//====================================
// 2D�|���S���̏���������(�f�t�H)
//====================================
HRESULT CScore::Init(void)
{
	SetType(TYPE_SCORE);

	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CScore::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	pos;
	rot;

	SetType(TYPE_SCORE);

	return S_FALSE;
	return S_OK;
}

//====================================
// 2D�|���S���̏�����(�ʒu�I�o��)
//====================================
HRESULT CScore::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, int nNum)
{
	D3DXVECTOR3 posDif = pos;
	m_nNum = nNum;

	for (int nCntCrt = 0; nCntCrt < nNum; nCntCrt++)
	{
		if (m_apNumber[nCntCrt] == nullptr)
		{
			m_apNumber[nCntCrt] = CNumber::Create(posDif, rot, size, 0);		//���g����

			posDif.x += size.x * 2;
		}
	}

	SetType(TYPE_SCORE);

	return S_OK;
}

//============================
// 2D�|���S���̏I������
//============================
void CScore::Uninit(void)
{
	for (int nCntCrt = 0; nCntCrt < MAX_SCORE; nCntCrt++)
	{
		if (m_apNumber[nCntCrt] != nullptr)
		{
			m_apNumber[nCntCrt]->Uninit();
			m_apNumber[nCntCrt] = nullptr;
		}
	}

	Release();
}

//============================
// 2D�|���S���̍X�V����
//============================
void CScore::Update(void)
{

}

//============================
// 2D�|���S���̕`�揈��
//============================
void CScore::Draw(void)
{

}

//============================
// 2D�|���S���̐�������
//============================
CScore * CScore::Create(void)
{
	CScore *pScore;

	//�I�u�W�F�N�g����
	pScore = new CScore;

	//������
	pScore->Init();

	return pScore;
}

//============================
// 2D�|���S���̐�������
//============================
CScore * CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, int nNum)
{
	CScore *pScore = nullptr;

	//�I�u�W�F�N�g����&������
	if (pScore == nullptr)
	{
		pScore = new CScore;

		if (pScore != nullptr)
		{
			pScore->Init(pos, rot, size, nNum);
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
void CScore::SetValue(int nValue)
{
	m_nValue = nValue; 

	int aTex[MAX_SCORE] = {};				//�e���̐������i�[
	int nCalc = nValue;

	//���l�̐ݒ�

	//�e�N�X�`�����W�̌v��
	for (int nCntScore = m_nNum - 1; nCntScore >= 0; nCntScore--)
	{
		aTex[nCntScore] = nCalc % 10;
		nCalc /= 10;
	}

	for (int nCntSet = 0; nCntSet < m_nNum; nCntSet++)
	{
		m_apNumber[nCntSet]->SetNumber(aTex[nCntSet]);
	}
}

//============================
// �X�R�A�l���Z
//============================
void CScore::CntValue(int nValue)
{
	m_nValue += nValue;

	SetValue(m_nValue);
}


//============================
// �ʒu�ݒ�
//============================
void CScore::SetPos(const D3DXVECTOR3 pos)
{
	pos;
}

//============================
// �����ݒ�
//============================
void CScore::SetRot(const D3DXVECTOR3 rot)
{
	rot;
}

//============================
// �ʒu�擾
//============================
D3DXVECTOR3 CScore::GetPos(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
// 2D�T�C�Y�擾
//============================
D3DXVECTOR3 CScore::GetSize(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
