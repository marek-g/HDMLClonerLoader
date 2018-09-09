#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>
#include "../../detours/detours.h"


static void Init()
{
}


//
// showRegistrationInfo
//

typedef void (*showRegistrationInfo)(void);
showRegistrationInfo _showRegistrationInfo = (showRegistrationInfo)0x489C24;

void __showRegistrationInfo(void)
{
	/*wchar_t buf[1024];
	swprintf(buf, L"__showRegistrationInfo()");
	OutputDebugString(buf);*/
}

//
// SetTimer
//

static UINT_PTR (WINAPI * _SetTimer)(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) = SetTimer;

UINT_PTR WINAPI __SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
{
	// ignore SetTimer longer then 1000 ms or with specific function
	// one of them checks if 30 minut elapsed and closes application

	if (uElapse <= 1000 && lpTimerFunc == 0)
	{
		return _SetTimer(hWnd, nIDEvent, uElapse, lpTimerFunc);
	}

	return 1234;
}

//
//
//
BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        
		Init();

		//DetourAttach(&(PVOID&)_showRegistrationInfo, __showRegistrationInfo);
		//DetourAttach(&(PVOID&)_SetTimer, __SetTimer);
       
		error = DetourTransactionCommit();

        if (error != NO_ERROR)
		{
			wchar_t buf[1024];
			swprintf(buf, L"Detour error: %d\n", error);
			MessageBox(0, buf, L"Detour", MB_OK);
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        
		//DetourDetach(&(PVOID&)_showRegistrationInfo, __showRegistrationInfo);
		//DetourDetach(&(PVOID&)_SetTimer, __SetTimer);
        
		error = DetourTransactionCommit();
    }
    return TRUE;
}

