#ifndef DINPUT_H
#define DINPUT_H

#include "../Core/cSingleton.h"

#include "cKeyboard.h"
#include "cMouse.h"

#define IS_USEKEYBOARD	1
#define IS_USEMOUSE		2

class cDirectInput/* : public cSingleton <cDirectInput>*/
{
public:
	cDirectInput ();

	bool Initialize(HWND hWnd, HINSTANCE appInstance, bool isExclusive = true, DWORD flags = IS_USEKEYBOARD | IS_USEMOUSE);
	bool Shutdown();

	void AcquireAll ();
	void UnacquireAll ();

	cKeyboard  *GetKeyboard() { return m_pKeyboard; }
	cMouse     *GetMouse()    { return m_pMouse; }

	bool  Update();

	bool  KeyDown(unsigned char key) { return (m_pKeyboard && m_pKeyboard->KeyDown(key)); }
	bool  KeyUp(unsigned char key) { return (m_pKeyboard && m_pKeyboard->KeyUp(key)); }

	bool  ButtonDown(int button) { return (m_pMouse && m_pMouse->ButtonDown(button)); }
	bool  ButtonUp(int button) { return (m_pMouse && m_pMouse->ButtonUp(button)); }
	void  GetMouseMovement(int &dx, int &dy) { if (m_pMouse) m_pMouse->GetMovement(dx, dy); }
	int   GetMouseWheelMovement() { return (m_pMouse) ? m_pMouse->GetWheelMovement() : 0; }

private:
	cKeyboard  *m_pKeyboard;
	cMouse     *m_pMouse;
  
	LPDIRECTINPUT8 m_pDI;
};

#endif