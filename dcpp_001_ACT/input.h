//===============================================
//
// όΝ(input.h)
// Author ϋόc ΐΛ
//
//===============================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include <Xinput.h>
#define DIRECTINPUT_VERSION (0x0800)			//rhΜxΞ}Np
#include <dinput.h>

//CuΜN
#pragma comment(lib,"xinput.lib")				//GamepadόΝΙKv
#pragma comment(lib,"dinput8.lib")				//όΝΙKv

//}Nθ`
#define NUM_KEY_MAX (256)		//L[ΜΕε
#define NUM_PAD_MAX (4)			//PADgp

//όΝNX(e)
class CInput
{
public:
	CInput();		//RXgN^
	~CInput();		//fXgN^
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//ϊ»()
	virtual void Uninit(void);			//IΉ(Ό)
	virtual void Update(void) = 0;		//XV(Ό)

protected:
	static LPDIRECTINPUT8 m_pInput;		//DirectInputIuWFNgΦΜ|C^
	LPDIRECTINPUTDEVICE8 m_pDevice;		//όΝfoCXΦΜ|C^

private:
	//CInputKeyboard *pKeyboard;
	//CInputGamepad *pGamepad;
	//CInputMouse *pMouse;
};

//L[{[hNX(q)
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();		//RXgN^
	~CInputKeyboard();		//fXgN^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//ϊ»()
	void Uninit(void);			//IΉ(Ό)
	void Update(void);			//XV(Ό)

	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }		//vXξρζΎ
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }		//gK[ξρζΎ
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }		//[XξρζΎ

	//void SetPress(int nKey) { m_aKeyState[nKey] = 128; }		//vXξρζΎ
	//void SetTrigger(int nKey) { m_aKeyStateTrigger[nKey] = 128; }		//gK[ξρζΎ
	//void SetRelease(int nKey) { m_aKeyStateRelease[nKey] = 128; }		//[XξρζΎ

protected:
	BYTE m_aKeyState[NUM_KEY_MAX];					//L[{[hΜvXξρ
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//L[{[hΜgK[ξρ
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//L[{[hΜ[Xξρ

private:

};

//PadNX(q)
class CInputGamepad : public CInput
{
public:
	//{^Μρ^
	typedef enum
	{
		BUTTON_UP = 0,			//γ{^
		BUTTON_DOWN,			//Ί{^
		BUTTON_LEFT,			//Ά{^
		BUTTON_RIGHT,			//E{^
		BUTTON_START,			//X^[g{^
		BUTTON_BACK,			//obN{^
		BUTTON_6,				//LXeBbN΅έ
		BUTTON_7,				//RXeBbN΅έ
		BUTTON_LB,				//LB{^
		BUTTON_RB,				//RB{^
		BUTTON_10,				//XeBbNgK[H
		BUTTON_11,				//XeBbNgK[H
		BUTTON_A,				//A{^
		BUTTON_B,				//B{^
		BUTTON_Y,				//Y{^
		BUTTON_X,				//X{^
		BUTTON_LSTICKX,			//LXeBbNX
		BUTTON_LSTICKY,			//LXeBbNY
		BUTTON_MAX
	}PADBUTTON;

	CInputGamepad();		//RXgN^
	~CInputGamepad();		//fXgN^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//ϊ»()
	void Uninit(void);			//IΉ()
	void Update(void);			//XV()

	bool GetPress(PADBUTTON button, int nPlayer) { return (m_aButtonState[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }	//int^Ν½ΤΜRg[[©πw·
	bool GetPadTrigger(PADBUTTON button, int nPlayer) { return (m_aButtonStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }
	bool GetPadRelease(PADBUTTON button, int nPlayer) { return (m_aButtonStateRelease[nPlayer].Gamepad.wButtons & (0x01 << button)) ? true : false; }

	//ΆXeBbN
	SHORT GetGameStickLXPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbLY; }
	SHORT GetGameStickLXTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbLY; }
	SHORT GetGameStickLXRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbLX; }
	SHORT GetGameStickLYRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbLY; }
	
	//EXeBbN
	SHORT GetGameStickRXPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYPress(int nPlayer) { return m_aButtonState[nPlayer].Gamepad.sThumbRY; }
	SHORT GetGameStickRXTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYTrigger(int nPlayer) { return m_aButtonStateTrigger[nPlayer].Gamepad.sThumbRY; }
	SHORT GetGameStickRXRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbRX; }
	SHORT GetGameStickRYRelease(int nPlayer) { return m_aButtonStateRelease[nPlayer].Gamepad.sThumbRY; }

protected:
	XINPUT_STATE m_aButtonState[BUTTON_MAX];			//PADΜvXξρ
	XINPUT_STATE m_aButtonStateTrigger[BUTTON_MAX];	//PADΜgK[ξρ
	XINPUT_STATE m_aButtonStateRelease[BUTTON_MAX];	//PADΜ[Xξρ
	
	//SHORT m_aStickState[NUM_PAD_MAX];			//PADΜXeBbNvXξρ
	//SHORT m_aStickStateTrigger[NUM_PAD_MAX];	//PADΜXeBbNgK[ξρ
	//SHORT m_aStickStateRelease[NUM_PAD_MAX];	//PADΜXeBbN[Xξρ

private:

};


//}EXNX(q)
class CInputMouse : public CInput
{
public:
	//{^Μρ^
	typedef enum
	{
		BUTTON_LEFT = 0,			//Ά{^
		BUTTON_RIGHT,				//E{^
		BUTTON_WHEEL,				//zC[΅έ
		BUTTON_MAX
	}BUTTON;

	//#define NUM_MOUSE_BUTTON (sizeof(DIMOUSESTATE2 rgbButtons) / sizeof(BYTE))			//\’Μzρ
	#define NUM_MOUSE_BUTTON (8)			//}EX{^zρ

	CInputMouse();		//RXgN^
	~CInputMouse();		//fXgN^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//ϊ»
	void Uninit(void);			//IΉ
	void Update(void);			//XV

	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }		//vXξρζΎ
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }		//gK[ξρζΎ
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }		//[XξρζΎ
	D3DXVECTOR3 GetPos() { return m_pos; }		//ΚuζΎ
	D3DXVECTOR3 GetChangePos() { return D3DXVECTOR3((float)MouseState.lX, (float)MouseState.lY, (float)MouseState.lZ); }		//ΚuζΎ
protected:
	BYTE m_aKeyState[NUM_MOUSE_BUTTON];					//L[{[hΜvXξρ
	BYTE m_aKeyStateTrigger[NUM_MOUSE_BUTTON];			//L[{[hΜgK[ξρ
	BYTE m_aKeyStateRelease[NUM_MOUSE_BUTTON];			//L[{[hΜ[Xξρ
	DIMOUSESTATE2 MouseState;		//SόΝξρΜΫΗ
private:
	D3DXVECTOR3 m_pos;	//Κu
};

#endif
