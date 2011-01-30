#include "../Core/cRoot.h"
#include "cDInput.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

#pragma comment( lib, "dinput8.lib" )	// Search For dinput8.lib While Linking
#pragma comment( lib, "dxguid.lib" )	// Search For dxguid.lib While Linking

cDirectInput::cDirectInput()
	: m_pKeyboard(0), m_pMouse(0), m_pDI(0)
{
}

/*****************************************************************************
 cDirectInput::Initialize()

 Initializes the input system. isExclusive should be set to true for exclusive
 mouse access, false otherwise. Flags should be a combination of
 IS_USEKEYBOARD and/or IS_USEMOUSE.
*****************************************************************************/
bool cDirectInput::Initialize(HWND hWnd, HINSTANCE appInstance, bool isExclusive, DWORD flags)
{
	m_pKeyboard = NULL;
	m_pMouse = NULL;

	// create the DI object
	if (FAILED(DirectInput8Create(appInstance,
									DIRECTINPUT_VERSION,
									IID_IDirectInput8,
									(void **)&m_pDI,
									NULL)))
	{
		LOG()->Print ("Could not create DirectInput 8 device");
		return false;
	}

	if (flags & IS_USEKEYBOARD)
	{
		m_pKeyboard = new cKeyboard(m_pDI, hWnd);
		if (m_pKeyboard == NULL)
		{
			LOG()->Print ("Could not initialize keyboard");
			return false;
		}
	}
  
	if (flags & IS_USEMOUSE)
	{
		m_pMouse = new cMouse(m_pDI, hWnd, isExclusive);
		if (m_pMouse == NULL)
		{
			LOG()->Print ("Could not initialize mouse");
			return false;
		}
	}

	LOG()->Print ("Successfully initialized cDirectInput system");
	return true;

} // end cDirectInput::Initialize()


/*****************************************************************************
 cDirectInput::Shutdown()

 Releases all objects and frees memory.
*****************************************************************************/
bool cDirectInput::Shutdown()
{
  UnacquireAll();
  if (m_pKeyboard)
  {
    delete m_pKeyboard;
    m_pKeyboard = NULL;
  }

  if (m_pMouse)
  {
    delete m_pMouse;
    m_pMouse = NULL;
  }

  if (m_pDI)
	if (FAILED(m_pDI->Release()))
	{
		LOG()->Print ("Could not release the DirectInput device");
		return false;
	}

  LOG()->Print ("Successfully deinitialized cDirectInput system");
  return true;
} // end cDirectInput::Shutdown()


/*****************************************************************************
 cDirectInput::Update()

 Queries the current state of all devices.
*****************************************************************************/
bool cDirectInput::Update()
{
  if (m_pKeyboard)
    m_pKeyboard->Update();
  if (m_pMouse)
    m_pMouse->Update();

  return true;
} // end cDirectInput::Update()


/*****************************************************************************
 cDirectInput::AcquireAll()

 Makes sure all input devices are acquired
*****************************************************************************/
void cDirectInput::AcquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Acquire();
  if (m_pMouse)
    m_pMouse->Acquire();
} // end cDirectInput::AcquireAll()


/*****************************************************************************
 cDirectInput::UnacquireAll()

 Unacquires all devices
*****************************************************************************/
void cDirectInput::UnacquireAll()
{
  if (m_pKeyboard)
    m_pKeyboard->Unacquire();
  if (m_pMouse)
    m_pMouse->Unacquire();
} // end cDirectInput::UnacquireAll()