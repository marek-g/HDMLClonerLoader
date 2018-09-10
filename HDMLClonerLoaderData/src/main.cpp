#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>
#include "../../detours/detours.h"


static void Init()
{
}


// window_layout

typedef int(__fastcall *window_layout)(int self, void *notUsed, signed int width, int height);
window_layout _window_layout = (window_layout)0x438770;


// helper methods

typedef int(__fastcall *sub_420C70)(int self, void *notUsed, int a2, int a3, int a4, int a5);
sub_420C70 _sub_420C70 = (sub_420C70)0x420C70;

typedef int(__fastcall *sub_42C3D0)(int self, void *notUsed, int a2);
sub_42C3D0 _sub_42C3D0 = (sub_42C3D0)0x42C3D0;

typedef int(__fastcall *sub_429300)(int self, void *notUsed);
sub_429300 _sub_429300 = (sub_429300)0x429300;

typedef int(__fastcall *sub_4282F0)(int self, void *notUsed);
sub_4282F0 _sub_4282F0 = (sub_4282F0)0x4282F0;

typedef BOOL(*sub_42E6F0)();
sub_42E6F0 _sub_42E6F0 = (sub_42E6F0)0x42E6F0;


//
// Some MFC methods
//

typedef void(__fastcall *cwnd_move_window)(int self, void *notUsed, int x, int y, int width, int height, BOOL repaint);
cwnd_move_window _cwnd_move_window = (cwnd_move_window)0x43FAAA; //0x44C6E0;

typedef BOOL(__fastcall *cwnd_show_window)(int self, void *notUsed, int cmdShow);
cwnd_show_window _cwnd_show_window = (cwnd_show_window)0x43FA98; //0x44C6EC;


int __fastcall __window_layout(int self, void *notUsed, signed int width, int height)
{
	int v3; // esi@1
	int result; // eax@1
	int v5; // edi@10
	int v6; // edi@15

	v3 = self;
	result = *(DWORD *)(self + 3000);
	if (!result)
	{
		result = *(DWORD *)(self + 2736);
		if (result)
		{
			_cwnd_move_window((self + 2704), 0, width - 25, 5, 13, 13, 1);
			_cwnd_move_window((v3 + 696), 0, width - 50, 5, 13, 13, 1);
			_cwnd_move_window((v3 + 896), 0, width - 75, 5, 13, 13, 1);
			_cwnd_move_window((v3 + 1096), 0, width - 100, 5, 13, 13, 1);
			if (*(DWORD *)(v3 + 2936))
			{
				if (*((void**)0x5229D4))
				{
					_sub_420C70((int)*((void**)0x5229D4), 0, 7, 30, width - 13, height - 100);
					if (*((DWORD *)*((void**)0x5229D4) + 447) != 1)
						_sub_42C3D0((v3 + 2904), 0, 0);
				}
				_cwnd_move_window((v3 + 1296), 0, 7, 30, width - 13, height - 100, 1);
				_cwnd_move_window((v3 + 2904), 0, 7, 30, width - 13, height - 100, 1);
				_cwnd_move_window((v3 + 1368), 0, width - 100, height - 35, 67, 12, 1);
				_cwnd_move_window((v3 + 1504), 0, width - 30, height - 35, 13, 13, 1);
				if (*(DWORD *)(v3 + 5408) && (signed int)*((WPARAM*)0x52248C) < 3)
				{
					_cwnd_move_window((v3 + 1704), 0, width / 2 - 129, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 96), 0, width / 2 - 197, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1904), 0, width / 2 - 265, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 496), 0, width / 2 - 61, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2504), 0, width / 2 + 5, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2104), 0, width / 2 + 91, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 296), 0, width / 2 + 159, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 2304), 0, width / 2 + 227, height - 50, 38, 38, 1);
					_cwnd_show_window((v3 + 496), 0, 5);
				}
				else
				{
					v5 = (width - 56) / 2;
					_cwnd_move_window((v3 + 2504), 0, v5, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2104), 0, v5 + 86, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 296), 0, v5 + 154, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 2304), 0, v5 + 222, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1704), 0, v5 - 68, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 96), 0, v5 - 136, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1904), 0, v5 - 204, height - 50, 38, 38, 1);
					_cwnd_show_window((v3 + 496), 0, 0);
				}
			}
			_sub_429300(*(int *)(v3 + 2992), 0);
			_sub_4282F0(*(int *)(v3 + 2996), 0);
			result = _sub_42E6F0();
			if (result)
			{
				if (*(DWORD *)(v3 + 5408) && (signed int)*((WPARAM*)0x52248C) < 3)
				{
					_cwnd_move_window((v3 + 1704), 0, width / 2 - 129, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1904), 0, width / 2 - 197, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 496), 0, width / 2 - 61, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2504), 0, width / 2 + 5, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2104), 0, width / 2 + 91, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 2304), 0, width / 2 + 159, height - 50, 38, 38, 1);
					_cwnd_show_window((v3 + 496), 0, 5);
				}
				else
				{
					v6 = (width - 56) / 2;
					_cwnd_move_window((v3 + 2504), 0, v6, height - 63, 56, 56, 1);
					_cwnd_move_window((v3 + 2104), 0, v6 + 86, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 2304), 0, v6 + 154, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1704), 0, v6 - 68, height - 50, 38, 38, 1);
					_cwnd_move_window((v3 + 1904), 0, v6 - 136, height - 50, 38, 38, 1);
					_cwnd_show_window((v3 + 496), 0, 0);
				}
				_cwnd_show_window((v3 + 96), 0, 0);
				result = _cwnd_show_window((v3 + 296), 0, 0);
			}
		}
	}
	return result;
}


//
// showHideButtons
//

typedef int (__fastcall *showHideButtons)(int self, void* notUsed, int show);
showHideButtons _showHideButtons = (showHideButtons)0x43B850;// 0x4396E0;

int __fastcall __showHideButtons(int self, void* notUsed, int show)
{
	wchar_t buf[1024];
	swprintf(buf, L"__showHideButtons(%d)", show);
	OutputDebugString(buf);

	*((int*)0x45E788) = 1; // set previous state to 1 to make method call work
	*(DWORD *)(self + 3000) = 0;
	return _showHideButtons(self, notUsed, 0);
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

		DetourAttach(&(PVOID&)_window_layout, __window_layout);
		//DetourAttach(&(PVOID&)_showHideButtons, __showHideButtons);
		//DetourAttach(&(PVOID&)_sub1, __sub1);
       
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
        
		DetourDetach(&(PVOID&)_window_layout, __window_layout);
		//DetourDetach(&(PVOID&)_showHideButtons, __showHideButtons);
		//DetourDetach(&(PVOID&)_sub1, __sub1);
        
		error = DetourTransactionCommit();
    }
    return TRUE;
}

