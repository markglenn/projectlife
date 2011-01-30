#include "cKeyboard.h"

// Include Paul Nettle's memory manager
#include "../Memory/mmgr.h"

cKeyboard::cKeyboard(LPDIRECTINPUT8 pDI, HWND hWnd)
{
  if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDev, NULL)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetDataFormat(&c_dfDIKeyboard)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
  {
    // error processing
  }

  if (FAILED(m_pDIDev->Acquire()))
  {
    // error processing
  }

  Clear();
}

cKeyboard::~cKeyboard()
{
  if (m_pDIDev)
  {
    m_pDIDev->Unacquire();
    m_pDIDev->Release();
  }
}

bool cKeyboard::Update()
{
  if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
  {
    if (FAILED(m_pDIDev->Acquire()))
    {
      return false;
    }
    if (FAILED(m_pDIDev->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
    {
      return false;
    }
  }
  return true;
}

/*****************************************************************************
 CKeyboard::Acquire()

 Acquires the keyboard
*****************************************************************************/
bool cKeyboard::Acquire()
{
  Clear();
  return (!FAILED(m_pDIDev->Acquire()));
}


/*****************************************************************************
 CKeyboard::Unacquire()

 Unacquires the keyboard
*****************************************************************************/
bool cKeyboard::Unacquire()
{
  Clear();
  return (!FAILED(m_pDIDev->Unacquire()));
}