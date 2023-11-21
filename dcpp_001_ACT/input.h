//===============================================
//
// ���͏���(input.h)
// Author ���c ����
//
//===============================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include <Xinput.h>
#define DIRECTINPUT_VERSION (0x0800)			//�r���h���̌x���Ώ��}�N���p
#include <dinput.h>

//���C�u�����̃����N
#pragma comment(lib,"xinput.lib")				//Gamepad���͏����ɕK�v
#pragma comment(lib,"dinput8.lib")				//���͏����ɕK�v

//�}�N����`
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔
#define NUM_PAD_MAX (4)			//PAD�g�p��

//���̓N���X(�e)
class CInput
{
public:
	CInput();		//�R���X�g���N�^
	~CInput();		//�f�X�g���N�^
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//������()
	virtual void Uninit(void);			//�I��(����)
	virtual void Update(void) = 0;		//�X�V(��������)

protected:
	static LPDIRECTINPUT8 m_pInput;		//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;		//���̓f�o�C�X�ւ̃|�C���^

private:
	//CInputKeyboard *pKeyboard;
	//CInputGamepad *pGamepad;
	//CInputMouse *pMouse;
};

//�L�[�{�[�h�N���X(�q)
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();		//�R���X�g���N�^
	~CInputKeyboard();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//������()
	void Uninit(void);			//�I��(����)
	void Update(void);			//�X�V(��������)

	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }		//�v���X���擾
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }		//�g���K�[���擾
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }		//�����[�X���擾

	//void SetPress(int nKey) { m_aKeyState[nKey] = 128; }		//�v���X���擾
	//void SetTrigger(int nKey) { m_aKeyStateTrigger[nKey] = 128; }		//�g���K�[���擾
	//void SetRelease(int nKey) { m_aKeyStateRelease[nKey] = 128; }		//�����[�X���擾

protected:
	BYTE m_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���

private:

};

//Pad�N���X(�q)
class CInputGamepad : public CInput
{
public:
	//�{�^���̗񋓌^
	typedef enum
	{
		BUTTON_UP = 0,			//��{�^��
		BUTTON_DOWN,			//���{�^��
		BUTTON_LEFT,			//���{�^��
		BUTTON_RIGHT,			//�E�{�^��
		BUTTON_START,			//�X�^�[�g�{�^��
		BUTTON_BACK,			//�o�b�N�{�^��
		BUTTON_6,				//L�X�e�B�b�N��������
		BUTTON_7,				//R�X�e�B�b�N��������
		BUTTON_LB,				//LB�{�^��
		BUTTON_RB,				//RB�{�^��
		BUTTON_10,				//�X�e�B�b�N�g���K�[�H
		BUTTON_11,				//�X�e�B�b�N�g���K�[�H
		BUTTON_A,				//A�{�^��
		BUTTON_B,				//B�{�^��
		BUTTON_Y,				//Y�{�^��
		BUTTON_X,				//X�{�^��
		BUTTON_LSTICKX,			//L�X�e�B�b�NX
		BUTTON_LSTICKY,			//L�X�e�B�b�NY
		BUTTON_MAX
	}PADBUTTON;

	CInputGamepad();		//�R���X�g���N�^
	~CInputGamepad();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//������()
	void Uninit(void);			//�I��()
	void Update(void);			//�X�V()

	bool GetPress(PADBUTTON button, int nPlayer) { return (m_aButtonState[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }	//int�^�͉��Ԃ̃R���g���[���[�����w��
	bool GetPadTrigger(PADBUTTON button, int nPlayer) { return (m_aButtonStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }
	bool GetPadRelease(PADBUTTON button, int nPlayer) { return (m_aButtonStateRelease[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }

	//���X�e�B�b�N
	SHORT GetGameStickLXPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbLY; }
	SHORT GetGameStickLXTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbLY; }
	SHORT GetGameStickLXRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbLY; }
	
	//�E�X�e�B�b�N
	SHORT GetGameStickRXPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbRY; }
	SHORT GetGameStickRXTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbRY; }
	SHORT GetGameStickRXRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbRY; }

protected:
	XINPUT_STATE m_aButtonState[BUTTON_MAX];			//PAD�̃v���X���
	XINPUT_STATE m_aButtonStateTrigger[BUTTON_MAX];	//PAD�̃g���K�[���
	XINPUT_STATE m_aButtonStateRelease[BUTTON_MAX];	//PAD�̃����[�X���
	
	//SHORT m_aStickState[NUM_PAD_MAX];			//PAD�̃X�e�B�b�N�v���X���
	//SHORT m_aStickStateTrigger[NUM_PAD_MAX];	//PAD�̃X�e�B�b�N�g���K�[���
	//SHORT m_aStickStateRelease[NUM_PAD_MAX];	//PAD�̃X�e�B�b�N�����[�X���

private:

};


//�}�E�X�N���X(�q)
class CInputMouse : public CInput
{
public:
	//�{�^���̗񋓌^
	typedef enum
	{
		BUTTON_LEFT = 0,			//���{�^��
		BUTTON_RIGHT,				//�E�{�^��
		BUTTON_WHEEL,				//�z�C�[����������
		BUTTON_MAX
	}BUTTON;

	//#define NUM_MOUSE_BUTTON (sizeof(DIMOUSESTATE2 rgbButtons) / sizeof(BYTE))			//�\���̔z��
	#define NUM_MOUSE_BUTTON (8)			//�}�E�X�{�^���z��

	CInputMouse();		//�R���X�g���N�^
	~CInputMouse();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//������
	void Uninit(void);			//�I��
	void Update(void);			//�X�V

	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }		//�v���X���擾
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }		//�g���K�[���擾
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }		//�����[�X���擾
	D3DXVECTOR3 GetPos() { return m_pos; }		//�ʒu�擾
	D3DXVECTOR3 GetChangePos() { return D3DXVECTOR3((float)MouseState.lX, (float)MouseState.lY, (float)MouseState.lZ); }		//�ʒu�擾
protected:
	BYTE m_aKeyState[NUM_MOUSE_BUTTON];					//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_MOUSE_BUTTON];			//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_MOUSE_BUTTON];			//�L�[�{�[�h�̃����[�X���
	DIMOUSESTATE2 MouseState;		//�S���͏��̕ۊ�
private:
	D3DXVECTOR3 m_pos;	//�ʒu
};

#endif
