//===============================================
//
// �Q�[��(game.cpp)
// Author: ���c ����
//
//===============================================

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "game.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "field.h"
#include "input.h"
#include "spawn.h"
#include "pause.h"
#include "fade.h"
#include "timer.h"
#include "growselecter.h"
#include "map.h"
#include "bg3D.h"

#include "block.h"
#include "blk_goal.h"
#include "blk_break.h"

//=========================
// �}�N����`
//=========================

#if _DEBUG
#define START_TIME (10)		//�X�^�[�g���b��
#else
#define START_TIME (120)		//�X�^�[�g���b��
#endif

//=========================
// �ÓI�����o�ϐ�
//=========================
CPlayer *CGame::m_pPlayer = nullptr;					//�v���C���[
CPause *CGame::m_pPause = nullptr;						//�|�[�Y
CTimer *CGame::m_pTimer = nullptr;						//�^�C�}�[
CMap *CGame::m_pMap = nullptr;						//�}�b�v

//============================
// �R���X�g���N�^
//============================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pPause = nullptr;
	m_pTimer = nullptr;
	m_pMap = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CGame::~CGame()
{

}

//============================
// ������
//============================
HRESULT CGame::Init()
{
	CScene::Init();

	//�I�u�W�F�N�g�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	CBg3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	m_pTimer->SetValue(START_TIME);

	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//�}�b�v����
	m_pMap = CMap::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pMap->Load("data\\SET\\MAP\\load.txt");
	m_pMap->Uninit();
	delete m_pMap;
	m_pMap = nullptr;

	return S_OK;
}

//============================
// �I��
//============================
void CGame::Uninit()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = nullptr;
	}
	
	CScene::Uninit();

	CManager::GetInstance()->GetSound()->Stop();
}

//============================
// �X�V
//============================
void CGame::Update()
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamepad *pInputPad = CManager::GetInstance()->GetInputGamepad();
	bool bPause = CManager::GetInstance()->GetPause();
	bool bEdit = CManager::GetInstance()->GetEdit();

	CScene::Update();

#if _DEBUG
	//�G�f�B�b�g
	if (pInputKeyboard->GetTrigger(DIK_M))
	{//[ M ]�L�[�ŃG�f�B�b�g

		if (m_pMap == nullptr)
		{
			m_pMap = CMap::Create(m_pPlayer->GetPos());
		}
		else
		{
			m_pMap->Uninit();
			delete m_pMap;
			m_pMap = nullptr;
		}

		CManager::GetInstance()->InvEdit();
	}

	if (m_pMap != nullptr && bEdit == true)
	{
		m_pMap->Update();
		return;
	}

#endif

	//�|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputPad->GetPress(CInputGamepad::BUTTON_START, 0) == true)
	{//[ P ]�L�[�Ń|�[�Y

		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
		else
		{
			m_pPause->Uninit();
			m_pPause = nullptr;
		}

		CManager::GetInstance()->InvPause();

		if (m_pTimer != nullptr)
		{
			m_pTimer->CntStop();
		}
	}

	if (m_pPause != nullptr && bPause == true)
	{
		m_pPause->Update();
	}

#if _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->SetResult(CManager::RT_WIN);
	}
#endif

	CFade *pFade = CScene::GetFade();

	if (CManager::GetInstance()->GetResult() != CManager::RT_NONE)
	{//���ʂ��m�肵����
		
		pFade->SetState(CScene::MODE_RESULT);

		if (m_pTimer != nullptr)
		{//�^�C�}�[�ۑ�

			m_pTimer->SetStop(true);
			SetNowTime(m_pTimer->GetValue());
		}
	}

	if (m_pTimer != nullptr)
	{//�^�C�}�[�X�V

	 //���Z
		m_pTimer->CntValue(1);
	}
}

//============================
// �`��
//============================
void CGame::Draw()
{
	if (m_pMap != nullptr)
	{
		m_pMap->Draw();
		return;
	}

	CScene::Draw();
}

//============================
// ����
//============================
CGame * CGame::Create()
{
	CGame *pGame = nullptr;

	//�I�u�W�F�N�g����&������
	pGame = new CGame;

	if (pGame != nullptr)
	{
		if (FAILED(pGame->Init()))
		{
			return nullptr;
		}
		else
		{

		}
	}
	else
	{
		return nullptr;
	}

	return pGame;
}
