//===============================================
//
// ����(main.cpp)
// Author ���c ����
//
//===============================================

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"

//=========================
// �}�N����`
//=========================
#define CLASS_NAME "WindowClass"				//�E�B���h�E�N���X�̖��O
#define ID_TIMER (131)							//�^�C�}�[��ID
#define TIMER_INTERVAL (1000/TIMER_FPS)				//�^�C�}�[�̔����Ԋu(�~���b)

//=========================
// �v���g�^�C�v�錾
//=========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=========================
// �O���[�o���ϐ�
//=========================
int g_nCountFPS = 0;							//FPS�J�E���^

//============================
// ���C���֐�
//============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//�I�����Ƀ��������[�N���o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DWORD dwCurrentTime;						//���ݎ���
	DWORD dwExecLastTime;						//�Ō�ɏ�����������
	DWORD dwFrameCount;							//�t���[���J�E���g
	DWORD dwFPSLastTime;						//�Ō��FPS���v����������

	WNDCLASSEX wcex 
	{
		sizeof(WNDCLASSEX),						//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,								//�E�B���h�E�̃X�^�C��
		WindowProc,								//�E�B���h�E�v���V�[�W��
		0,										//0�ɂ���i�ʏ�g�p���Ȃ��j
		0,										//0�ɂ���i�ʏ�g�p���Ȃ��j
		hInstance,								//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),			//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),				//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),				//�N���C�A���g�̈�̔w�i�F(+ 0�`26�̐��l��ς��邱�ƂŐF���ς��)
		//(HBRUSH)(COLOR_WINDOW + 1),			//�ς���Ȃ��H
		NULL,									//���j���[�o�[
		CLASS_NAME,								//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)			//�t�@�C���̃A�C�R��
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,			//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,					//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),		//�E�B���h�E�̉���
		(rect.bottom - rect.top),		//�E�B���h�E�̏c��
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�쐬�f�[�^

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;					//������
	dwExecLastTime = timeGetTime();		//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�}�l�[�W���̏�����
	if (FAILED(CManager::GetInstance()->Init(hInstance, hWnd, TRUE)))
	{
		return E_FAIL;
	}

	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);			//�E�B���h�E�̕\����Ԃ�ݒ�
				DispatchMessage(&msg);			//�N���C�A���g�̈���X�V			
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();		//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS�𑪒�
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= TIMER_INTERVAL)
			{//60����1�b�o��

				dwExecLastTime = dwCurrentTime;		//�����J�n����[���ݎ���]��ۑ�

				//DirectX�̏���
				//�}�l�[�W���̍X�V
				CManager::GetInstance()->Update();

				//�}�l�[�W���̕`��
				CManager::GetInstance()->Draw();

				dwFrameCount++;
			}
		
		}
	}

	CManager::Release();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//============================
// �E�B���h�E�v���V�[�W��
//============================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{//
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:		//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//{ESC}�L�[�������ꂽ

			int nNumCsr = 0;

			nNumCsr = ShowCursor(true);

			do
			{//�J�[�\���\������true(1)�ɂ��邽�߃��[�v

				if (nNumCsr > 1)
				{
					nNumCsr = ShowCursor(false);
				}
				else if (nNumCsr < 1)
				{
					nNumCsr = ShowCursor(true);
				}

			} while (nNumCsr != 1);

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_CLOSE:			//����{�^�������̃��b�Z�[�W

		int nNumCsr = 0;
	
		do
		{//�J�[�\���\������true(1)�ɂ��邽�߃��[�v

			nNumCsr = ShowCursor(true);

			if (nNumCsr > 1)
			{
				nNumCsr = ShowCursor(false);
			}
			else if (nNumCsr < 1)
			{
				nNumCsr = ShowCursor(true);
			}

		} while (nNumCsr != 1);

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;		//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//����̏�����Ԃ�
}

//=================================
// FPS�擾
//=================================
int GetFPS(void)
{
	return g_nCountFPS;
}
