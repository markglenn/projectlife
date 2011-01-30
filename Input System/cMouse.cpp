#include "cMouse.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

/*****************************************************************************
 CMouse::Constructor

 Initializes the DI device
*****************************************************************************/
cMouse::cMouse(LPDIRECTINPUT8 pDI, HWND hWnd, bool isExclusive)
{
  if (FAILED(pDI->CreateDevice(GUID_SysMouse, &m_pDIDev, NULL)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIMouse)))
  {
    // error processing
  }

  DWORD flags;
  if (isExclusive)
    flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
  else
    flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;


  if (FAILED(m_pDIDev->SetCooperativeLevel(hWnd, flags)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    // error processing
  }
} // end CMouse::Constructor


/*****************************************************************************
 CMouse::Destructor

 Releases the DI device
*****************************************************************************/
cMouse::~cMouse()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
} // end CMouse::Destructor


/*****************************************************************************
 CMouse::Update()

 Queries the current state of the mouse and stores it in the member
 variables.
*****************************************************************************/
bool cMouse::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(DIMOUSESTATE), &m_state)))
    {
      return false;
    }
  }

  return true;
} // end CMouse::Update()


/*****************************************************************************
 CMouse::Acquire()

 Acquires the mouse
*****************************************************************************/
bool cMouse::Acquire()
{
  return (!FAILED(m_pDIDev->Acquire()));
} // end CMouse::Acquire


/*****************************************************************************
 CMouse::Unacquire()

 Unacquires the keyboard
*****************************************************************************/
bool cMouse::Unacquire()
{
  return (!FAILED(m_pDIDev->Unacquire()));
} // end CMouse::Unacquire()

