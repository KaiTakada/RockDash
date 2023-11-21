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
#include "item2D.h"
#include "game.h"
#include "growselecter.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"

//=======================
//�}�N����`
//=======================
#define MAX_PAUSE (MAX_ITEM)			//�|�[�Y�̑I������
#define EVO_MID (200)						//�|�[�Y�̑I�����ǂ����̊ԁi���j
#define EVO_SIZE D3DXVECTOR3(250.0f,30.0f,0.0f)			//�^�C�g�����̃T�C�Y
#define EVO_SIZE_BG D3DXVECTOR3(350.0f,400.0f,0.0f)			//�^�C�g�����̃T�C�Y
#define EVO_BG_FILE "data\\TEXTURE\\ITEM\\bg.png"		//Bg�t�@�C���p�X

//=======================
// �ÓI�����o�ϐ�
//=======================

//============================
// �R���X�g���N�^
//============================
CGrowSelecter::CGrowSelecter(int nPriority) : CObject(nPriority)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
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
CGrowSelecter::~CGrowSelecter()
{

}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CGrowSelecter::Init()
{
	float fMid = -EVO_MID * (MAX_ITEM / 2);

	m_pBg = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(EVO_SIZE_BG.x, EVO_SIZE_BG.y, EVO_SIZE_BG.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(quit)

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		m_pItem[nCntItem] = CItem2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + fMid, SCREEN_HEIGHT * 0.5f, 0.0f), CItem2D::TYPE(rand() % CItem2D::TYPE_MAX));			//�I����(quit)
	
		fMid += EVO_MID;
	}

	m_nPauseSelect = 0;

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CGrowSelecter::Init(const D3DXVECTOR3 pos)
{
	m_pBg = CObject2D::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(EVO_SIZE_BG.x, EVO_SIZE_BG.y, EVO_SIZE_BG.z), CObject2D::UPDATE_TYPE_NONE);			//�I����(bg)

	//�Ԋu�������p��
	float fMid = -EVO_MID * (MAX_ITEM / 2);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		m_pItem[nCntItem] = CItem2D::Create(D3DXVECTOR3(pos.x, pos.y + fMid, 0.0f), CItem2D::TYPE_000_HEAL);			//�I����(quit)

		fMid += EVO_MID;
	}

	m_nPauseSelect = 0;

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	return S_OK;
}

//============================
// �I��
//============================
void CGrowSelecter::Uninit(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
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
void CGrowSelecter::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamepad *pInputPad = CManager::GetInstance()->GetInputGamepad();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();
	CFade *pFade = CScene::GetFade();
	int nNum[2] = {};

	if (pInputKeyboard->GetTrigger(DIK_A) || pInputPad->GetPress(CInputGamepad::BUTTON_LEFT, 0) == true)
	{
		nNum[0] = m_nPauseSelect;

		m_nPauseSelect--;

		if (m_nPauseSelect < 0)
		{//�����˔j��
			m_nPauseSelect = MAX_ITEM - 1;
		}
	
		nNum[1] = m_nPauseSelect;
	}
	else if (pInputKeyboard->GetTrigger(DIK_D) || pInputPad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) == true)
	{
		nNum[0] = m_nPauseSelect;

		m_nPauseSelect++;

		m_nPauseSelect %= MAX_ITEM;

		nNum[1] = m_nPauseSelect;
	}

	if (nNum[0] != nNum[1])
	{//�I��悪�ς������A�I�����̐F�ς�
		m_pItem[nNum[0]]->SetTexCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
		m_pItem[nNum[1]]->SetTexCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) || pInputKeyboard->GetTrigger(DIK_SPACE) || 
		pInputPad->GetPress(CInputGamepad::BUTTON_A, 0) == true)
		&& m_bEnter == false)
	{
		m_bEnter = true;

		//Player�Ɍ��ʂ�t�^����̂͂ǂ����̕��������Hevo?item2D?
		m_pItem[m_nPauseSelect]->PlayerAdd();

		CPlayer *pPlayer = CGame::GetPlayer();
		
		if (pPlayer != nullptr)
		{
		
		}
		else
		{
			pPlayer = nullptr;
		}

		CManager::GetInstance()->SetGrow(false);
		Uninit();
		return;
	}
}

//============================
// �`��
//============================
void CGrowSelecter::Draw(void)
{

}

//============================
// �|�[�Y�̐���
//============================
CGrowSelecter * CGrowSelecter::Create()
{
	CGrowSelecter *pPause = nullptr;

	//�I�u�W�F�N�g����&������
	pPause = new CGrowSelecter;

	if (pPause != nullptr)
	{
		if (FAILED(pPause->Init()))
		{
			return nullptr;
		}
		else
		{
			CTexture *pTexture = CManager::GetInstance()->GetTexture();

			for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
			{
				if (pPause->m_pItem[nCntItem] != nullptr)
				{
					if (pPause->m_nPauseSelect != nCntItem)
					{
						pPause->m_pItem[nCntItem]->SetTexCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
					}
				}
			}
			
			pPause->m_pBg->SetTexCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f));
			pPause->m_pBg->SetIdxTexture(-1);
			//pPause->m_pBg->SetIdxTexture(pTexture->Regist(EVO_BG_FILE));
		}
	}
	else
	{
		return nullptr;
	}

	return pPause;
}
