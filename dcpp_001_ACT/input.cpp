//===============================================
//
// ���͏���(input.cpp)
// Author ���c ����
//
//===============================================
#include "input.h"

//======================================
// �ÓI�����o�ϐ��錾
//======================================
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//======================================
// [����]�R���X�g���N�^
//======================================
CInput::CInput() 
{
	//m_pInput = nullptr;
	m_pDevice = nullptr;
}

//======================================
// [����]�f�X�g���N�^
//======================================
CInput::~CInput()
{

}

//======================================
// [����]������
//======================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//======================================
// [����]�I��(����)
//======================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//========================= �L�[�{�[�h =========================
//======================================
// [�L�[�{�[�h]�R���X�g���N�^
//======================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
		m_aKeyStateRelease[nCnt] = 0;
	}
}

//======================================
// [�L�[�{�[�h]�f�X�g���N�^
//======================================
CInputKeyboard::~CInputKeyboard()
{

}

//======================================
// [�L�[�{�[�h]������
//======================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != nullptr)
	{
		//���̓f�o�C�X(�L�[�{�[�h)�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//�f�[�^�t�H�[�}�b�g�̐ݒ�
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//�������[�h��ݒ�
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();

		return S_OK;
	}

	return E_FAIL;
}

//======================================
// [�L�[�{�[�h]�I��
//======================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//======================================
// [�L�[�{�[�h]�X�V
//======================================
void CInputKeyboard::Update(void)
{
 	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCntKey;

	if (GetTrigger(DIK_RETURN))
	{
		int n;
		n = 1;
	}

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];		//�L�[�{�[�h�̃����[�X����ۗL
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//�L�[�{�[�h�̃g���K�[����ۗL
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۗL
		}
	}
	else
	{
		m_pDevice->Acquire();						//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//========================= XPad =========================
//======================================
// [XPad]�R���X�g���N�^
//======================================
CInputGamepad::CInputGamepad()
{
	XInputEnable(true);

	for (int nCnt = 0; nCnt < NUM_PAD_MAX; nCnt++)
	{
		//���������N���A
		memset(&m_aButtonState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_aButtonStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_aButtonStateRelease[nCnt], 0, sizeof(XINPUT_STATE));
	}
}

//======================================
// [XPad]�f�X�g���N�^
//======================================
CInputGamepad::~CInputGamepad()
{

}

//======================================
// [XPad]������
//======================================
HRESULT CInputGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}

//======================================
// [XPad]�I��
//======================================
void CInputGamepad::Uninit(void)
{
	CInput::Uninit();

	XInputEnable(false);
}

//======================================
// [XPad]�X�V
//======================================
void CInputGamepad::Update(void)
{
	XINPUT_STATE aButtonState[NUM_PAD_MAX];			//�{�^���̓��͏��
	//XINPUT_STATE aStickState[NUM_KEY_MAX];		//�X�e�B�b�N�̓��͏��
	static int nCntSpace = 0;						//�X�y�[�X

	//���̓f�o�C�X����f�[�^�擾
	for (int nCntKey = 0; nCntKey < NUM_PAD_MAX; nCntKey++)
	{
		if ((XInputGetState(nCntKey, &aButtonState[nCntKey])) == ERROR_SUCCESS)
		{
			m_aButtonStateRelease[nCntKey].Gamepad.wButtons = (m_aButtonState[nCntKey].Gamepad.wButtons ^ aButtonState[nCntKey].Gamepad.wButtons) & m_aButtonState[nCntKey].Gamepad.wButtons;		//�L�[�{�[�h�̃����[�X����ۗL
			m_aButtonStateTrigger[nCntKey].Gamepad.wButtons = (m_aButtonState[nCntKey].Gamepad.wButtons ^ aButtonState[nCntKey].Gamepad.wButtons) & aButtonState[nCntKey].Gamepad.wButtons;		//�L�[�{�[�h�̃g���K�[����ۗL
			m_aButtonState[nCntKey].Gamepad.wButtons = aButtonState[nCntKey].Gamepad.wButtons;		//�L�[�{�[�h�̃v���X����ۗL

			//�X�e�B�b�N Release��Trigger�͂��邢
			m_aButtonState[nCntKey].Gamepad = aButtonState[nCntKey].Gamepad;
		}
	}
}

//========================= �}�E�X =========================
//======================================
// [�}�E�X]�R���X�g���N�^
//======================================
CInputMouse::CInputMouse()
{
	for (int nCnt = 0; nCnt < NUM_MOUSE_BUTTON; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
		m_aKeyStateRelease[nCnt] = 0;
		MouseState.rgbButtons[nCnt] = 0;
	}

	MouseState.lX = 0;
	MouseState.lY = 0;
	MouseState.lZ = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �}�E�X���W���擾����
	POINT p;
	if (GetCursorPos(&p))
	{
		// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
		ScreenToClient(FindWindowA(WINDOW_NAME, nullptr), &p);

		m_pos = D3DXVECTOR3(float(p.x), float(p.y), 0.0f);
	}
}

//======================================
// [�}�E�X]�f�X�g���N�^
//======================================
CInputMouse::~CInputMouse()
{

}

//======================================
// [�}�E�X]������
//======================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != nullptr)
	{
		//���̓f�o�C�X(�}�E�X)�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//�f�[�^�t�H�[�}�b�g�̐ݒ�
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
		{
			return E_FAIL;
		}

		//�������[�h��ݒ�
		if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		//�f�o�C�X�̐ݒ�
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL;	//���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

		if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			//�f�o�C�X�̐ݒ�Ɏ��s
			return E_FAIL;
		}

		//�}�E�X�ւ̃A�N�Z�X�����l��
		m_pDevice->Acquire();
	
		return S_OK;
	}

	return E_FAIL;
}

//======================================
// [�}�E�X]�I��
//======================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//======================================
// [�}�E�X]�X�V
//======================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouse;	//�}�E�X�̓��͏��

	//���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCntKey = 0; nCntKey < NUM_MOUSE_BUTTON; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (MouseState.rgbButtons[nCntKey] ^ mouse.rgbButtons[nCntKey]) & mouse.rgbButtons[nCntKey];				//�L�[�{�[�h�̃g���K�[����ۗL
			m_aKeyStateRelease[nCntKey] = (MouseState.rgbButtons[nCntKey] ^ mouse.rgbButtons[nCntKey]) & MouseState.rgbButtons[nCntKey];		//�L�[�{�[�h�̃����[�X����ۗL
			m_aKeyState[nCntKey] = mouse.rgbButtons[nCntKey];					//�L�[�{�[�h�̃v���X����ۗL
			MouseState.rgbButtons[nCntKey] = mouse.rgbButtons[nCntKey];			//�L�[�{�[�h�̃v���X����ۗL
		}

		MouseState = mouse;
		m_pos += D3DXVECTOR3((float)mouse.lX, (float)mouse.lY, (float)mouse.lZ);
	}
	else
	{
		m_pDevice->Acquire();	//�}�E�X�ւ̃A�N�Z�X�����l��
	}
}