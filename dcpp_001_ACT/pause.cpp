//===============================================
//
// �|�[�Y��ʂ̏���(pause.cpp)
// Author:Kai Takada
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "texture.h"	//�`��e�N�X�`��
#include "object2D.h"
#include "game.h"
#include "pause.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//=======================
//�}�N����`
//=======================
#define MAX_PAUSE (PAUSE_MENU_MAX)			//�|�[�Y�̑I������
#define PAUSE_MID (100)						//�|�[�Y�̑I�����ǂ����̊ԁi�c�j
#define PAUSE_SIZE D3DXVECTOR3(250.0f,30.0f,0.0f)			//�^�C�g�����̃T�C�Y
#define PAUSE_SIZE_BG D3DXVECTOR3(350.0f,400.0f,0.0f)			//�^�C�g�����̃T�C�Y

//=======================
// �t�@�C���p�X
//=======================
const char *c_apFilenamePause[] =
{
	"data\\TEXTURE\\PAUSE\\continue.png",
	"data\\TEXTURE\\PAUSE\\retry.png",
	"data\\TEXTURE\\PAUSE\\quit.png",
	"data\\TEXTURE\\PAUSE\\Bg.png",
};

//=======================
// �ÓI�����o�ϐ�
//=======================

//============================
// �R���X�g���N�^
//============================
CPause::CPause(int nPriority) : CObject(nPriority)
{
	for (int nCntItem = 0; nCntItem < PAUSE_MENU_MAX; nCntItem++)
	{
		m_pItem[nCntItem] = nullptr;		//�I����(continue)
	}

	m_pBg = nullptr;			//�w�i()
	m_nPauseSelect = 0;			//���݂̑I����
	m_bEnter = false;
}

//============================
// �f�X�g���N�^
//============================
CPause::~CPause()
{

}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CPause::Init()
{
	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(PAUSE_SIZE_BG.x, PAUSE_SIZE_BG.y, PAUSE_SIZE_BG.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(quit)

	for (int nCntItem = 0; nCntItem < PAUSE_MENU_MAX; nCntItem++)
	{
		m_pItem[nCntItem] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_WIDTH * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(PAUSE_SIZE.x, PAUSE_SIZE.y, PAUSE_SIZE.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(quit)
	}

	m_nPauseSelect = 0;

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CPause::Init(const D3DXVECTOR3 pos)
{
	m_pBg = CObject2D::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(PAUSE_SIZE_BG.x, PAUSE_SIZE_BG.y, PAUSE_SIZE_BG.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(bg)

	//�Ԋu�������p��
	float fMid = -PAUSE_MID * (PAUSE_MENU_MAX / 2);

	for (int nCntItem = 0; nCntItem < PAUSE_MENU_MAX; nCntItem++)
	{
		m_pItem[nCntItem] = CObject2D::Create(D3DXVECTOR3(pos.x, pos.y + fMid, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(PAUSE_SIZE.x, PAUSE_SIZE.y, PAUSE_SIZE.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(quit)

		fMid += PAUSE_MID;
	}

	m_nPauseSelect = 0;

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	return S_OK;
}

//============================
// �I��
//============================
void CPause::Uninit(void)
{
	for (int nCntItem = 0; nCntItem < PAUSE_MENU_MAX; nCntItem++)
	{
		if (m_pItem[nCntItem] != nullptr)
		{
			m_pItem[nCntItem]->Uninit();
			m_pItem[nCntItem] = nullptr;
		}
	}

	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	Release();
}

//============================
// �X�V
//============================
void CPause::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CFade *pFade = CScene::GetFade();
	int nNum[2] = {};

	if (pInputKeyboard->GetTrigger(DIK_W))
	{
		nNum[0] = m_nPauseSelect;

		m_nPauseSelect--;

		if (m_nPauseSelect < 0)
		{//�����˔j��
			m_nPauseSelect = PAUSE_MENU_MAX - 1;
		}
	
		nNum[1] = m_nPauseSelect;
	}
	else if (pInputKeyboard->GetTrigger(DIK_S))
	{
		nNum[0] = m_nPauseSelect;

		m_nPauseSelect++;

		m_nPauseSelect %= PAUSE_MENU_MAX;

		nNum[1] = m_nPauseSelect;
	}

	if (nNum[0] != nNum[1])
	{//�I��悪�ς������A�I�����̐F�ς�
		m_pItem[nNum[0]]->SetTexCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
		m_pItem[nNum[1]]->SetTexCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) && m_bEnter == false)
	{
		m_bEnter = true;

		switch (m_nPauseSelect)
		{
			case PAUSE_MENU_CONTINUE:
				CManager::GetInstance()->SetPause(false);
				CGame::NullPause();
				Uninit();
				break;

			case PAUSE_MENU_RETRY:
				pFade->SetState(CScene::MODE_GAME);
				break;

			case PAUSE_MENU_QUIT:
				pFade->SetState(CScene::MODE_TITLE);
				break;

			default:

			break;
		}
	}
}

//============================
// �`��
//============================
void CPause::Draw(void)
{

}

//============================
// �|�[�Y�̐���
//============================
CPause * CPause::Create(D3DXVECTOR3 pos)
{
	CPause *pPause = nullptr;

	//�I�u�W�F�N�g����&������
	pPause = new CPause;

	if (pPause != nullptr)
	{
		if (FAILED(pPause->Init(pos)))
		{
			return nullptr;
		}
		else
		{
			CTexture *pTexture = CManager::GetInstance()->GetTexture();

			for (int nCntItem = 0; nCntItem < PAUSE_MENU_MAX; nCntItem++)
			{
				if (pPause->m_pItem[nCntItem] != nullptr)
				{
					if (pPause->m_nPauseSelect != nCntItem)
					{
						pPause->m_pItem[nCntItem]->SetTexCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
					}
					
					pPause->m_pItem[nCntItem]->SetIdxTexture(pTexture->Regist(c_apFilenamePause[nCntItem]));
				}
			}
			
			pPause->m_pBg->SetTexCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f));
			pPause->m_pBg->SetIdxTexture(-1);
			//pPause->m_pBg->SetIdxTexture(pTexture->Regist(c_apFilenamePause[PAUSE_MENU_MAX]));
		}
	}
	else
	{
		return nullptr;
	}

	return pPause;
}
