//==========================================
//
// fade.cpp
// Author: ���c ����
//
// �R�����g�m�F���ׂ��B
//==========================================
#include "fade.h"
#include "input.h"

//===========================
// �}�N����`
//===========================
#define COL_A_ADD (1.0f / 80.0f)

//===========================
// �R���X�g���N�^
//===========================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_state = STATE_NONE;								//�t�F�[�h�̏��
	m_modeNext = CScene::MODE_TITLE;						//���̉��(���[�h)
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�|���S��(�t�F�[�h)�̐F
	m_bExc = false;
}

//===========================
// �f�X�g���N�^
//===========================
CFade::~CFade()
{

}

//===========================
//�t�F�[�h�̏���������
//===========================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	CObject2D::Init(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_state = STATE_IN;									//�m���t�F�[�h��Ԃ�

	m_modeNext = modeNext;									//���̉�ʁi���[�h�j��ݒ�

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//�����|�C�S���i�s�����j�ɂ��Ă���
	
	SetTexCol(m_colorFade);
	
	//SetState(m_modeNext);

	SetType(TYPE_FADE);

	return S_OK;
}

//===========================
//�t�F�[�h�̏I������
//===========================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================
//�t�F�[�h�̍X�V����
//===========================
void CFade::Update(void)
{
	CObject2D::Update();

	if (m_state != STATE_NONE)
	{
		if (m_state == STATE_IN)
		{//�t�F�[�h�C�����
			m_colorFade.a -= COL_A_ADD;					//�|���S���𓧖��ɂ��Ă���

			if (m_colorFade.a < 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_state = STATE_NONE;					//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_state == STATE_OUT)
		{//�t�F�[�h�A�E�g���
			m_colorFade.a += COL_A_ADD;					//�|���S����s�����ɂ��Ă���

			if (m_colorFade.a > 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_state = STATE_NONE;					//�t�F�[�h�C����Ԃ�

				m_bExc = false;

				//���[�h�ݒ�i���̉�ʂɈڍs�j
				CManager::GetInstance()->SetMode(m_modeNext);

				return;
			}
		}

		//�F�ς�
		SetTexCol(m_colorFade);
	}
}
//===========================
//�t�F�[�h�̕`�揈��
//===========================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//===========================
// ��������
//===========================
CFade *CFade::Create(CScene::MODE modeNext)
{
	CFade *pFade = nullptr;

	//�I�u�W�F�N�g����&������
	pFade = new CFade;

	if (pFade != nullptr)
	{
		if (FAILED(pFade->Init(modeNext)))
		{
			return nullptr;
		}
		else
		{
			pFade->SetIdxTexture(-1);

			pFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
			pFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
	}
	else
	{
		return nullptr;
	}


	return pFade;
}

//===========================
// �t�F�[�h�̐ݒ菈��
//===========================
bool CFade::SetState(CScene::MODE modeNext)
{
	if (m_bExc == false)
	{
		m_bExc = true;

		m_state = STATE_OUT;									//�t�F�[�h�A�E�g��Ԃ�

		m_modeNext = modeNext;									//���̉�ʁi���[�h�j��ݒ�

		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�����|�C�S���i�����j�ɂ��Ă���	
		SetTexCol(m_colorFade);
	
		return true;
	}

	return false;
}
