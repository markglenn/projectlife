#include <windows.h>

#include "cTestApplication.h"

// Include Paul Nettle's memory manager
#include "Memory/mmgr.h"

//using namespace std;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR cmd, int cmdShow)
{
	cTestApplication application;

	application.InitializeEngine(hInstance);

	if (!application.Run ())
		MessageBox (NULL, "Check Log.txt for errors", "An Error Has Occurred", MB_OK);

	return 0;
}
