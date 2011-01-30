#ifndef KEYBOARD_H
#define KEYBOARD_H

#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <winuser.h>
#include <dinput.h>

class cKeyboard 
{
public:
	cKeyboard(LPDIRECTINPUT8 pDI, HWND hWnd);
	~cKeyboard();

	bool KeyDown(unsigned char key) { return (m_keys[key] & 0x80) ? true : false; }
	bool KeyUp(unsigned char key) { return (m_keys[key] & 0x80) ? false : true; }

	bool Update();

	void Clear() { ZeroMemory(m_keys, 256 * sizeof(char)); }

	bool Acquire();
	bool Unacquire();

private:
	LPDIRECTINPUTDEVICE8 m_pDIDev;

	unsigned char m_keys[256];
};

#endif