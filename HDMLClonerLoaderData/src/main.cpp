#include <stdio.h>
#include <windows.h>
#include <MMSystem.h>
#include "../../detours/detours.h"


static void Init()
{
}


// Variables

DWORD *_is_top_most_ptr = (DWORD*)0x52554C;
DWORD *_keep_apect_rate_ptr = (DWORD*)0x525490;
DWORD *_auto_hide_buttons_ptr = (DWORD*)0x525550;


// WindowProc

typedef int(__fastcall *window_proc)(int self, void *notUsed, unsigned int wParam, unsigned int uMsg, unsigned int lParam);
window_proc _window_proc = (window_proc)0x43B9C0;


// window_layout

typedef int(__fastcall *window_layout)(int self, void *notUsed, signed int width, int height);
window_layout _window_layout = (window_layout)0x43A1C0;



// helper methods

typedef int(__fastcall *sub_421090)(int self, void *notUsed, int a2, int a3, int a4, int a5);
sub_421090 _sub_421090 = (sub_421090)0x421090;

typedef int(__fastcall *sub_42D6E0)(int self, void *notUsed, int a2);
sub_42D6E0 _sub_42D6E0 = (sub_42D6E0)0x42D6E0;

typedef int(__fastcall *sub_42D5C0)(int self, void *notUsed, int a2, int a3, int a4, int a5, int a6);
sub_42D5C0 _sub_42D5C0 = (sub_42D5C0)0x42D5C0;

typedef int(__fastcall *sub_429CF0)(int self, void *notUsed);
sub_429CF0 _sub_429CF0 = (sub_429CF0)0x0429CF0;

typedef int(__fastcall *sub_428CE0)(int self, void *notUsed);
sub_428CE0 _sub_428CE0 = (sub_428CE0)0x428CE0;

typedef BOOL(*sub_42FA80)();
sub_42FA80 _sub_42FA80 = (sub_42FA80)0x42FA80;


//
// Some MFC methods
//

typedef void(__fastcall *cwnd_move_window)(int self, void *notUsed, int x, int y, int width, int height, BOOL repaint);
cwnd_move_window _cwnd_move_window = (cwnd_move_window)0x441A2A; // ?MoveWindow@CWnd@@QAEXHHHHH@Z MFC42

typedef BOOL(__fastcall *cwnd_show_window)(int self, void *notUsed, int cmdShow);
cwnd_show_window _cwnd_show_window = (cwnd_show_window)0x441A18; // ?ShowWindow@CWnd@@QAEHH@Z MFC42


//
// __window_proc
//

int __fastcall __window_proc(int self, void *notUsed, unsigned int wParam, unsigned int uMsg, unsigned int lParam)
{
	if ((wParam == WM_NCRBUTTONUP || wParam == WM_RBUTTONUP) &&
		!*(DWORD *)(self + 3232))
	{
		// create popup menu

		HWND hWnd = *((HWND *)self + 8);

		HMENU mainMenu = CreatePopupMenu();

		AppendMenu(mainMenu, 0, 0x64, L"Zawsze na wierzchu");
		if (*_is_top_most_ptr)
		{
			CheckMenuItem(mainMenu, 0x64, MF_CHECKED);
		}
		AppendMenu(mainMenu, 0, MF_SEPARATOR, 0);
		AppendMenu(mainMenu, 0, 0x65, L"Zachowaj aspekt");
		if (*_keep_apect_rate_ptr)
		{
			CheckMenuItem(mainMenu, 0x65, MF_CHECKED);
		}
		AppendMenuA(mainMenu, 0, MF_SEPARATOR, 0);

		HMENU subMenu1 = CreatePopupMenu();
		AppendMenu(subMenu1, 0, 0xC8, L"16:9");
		AppendMenu(subMenu1, 0, 0xC9, L"16:10");
		AppendMenu(subMenu1, 0, 0xCA, L"4:3");
		AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subMenu1, L"Ustaw aspekt");

		AppendMenu(mainMenu, 0, MF_SEPARATOR, 0);
		AppendMenu(mainMenu, 0, 0x66, L"Ukrywaj przyciski");
		if (*_auto_hide_buttons_ptr)
		{
			CheckMenuItem(mainMenu, 0x66, MF_CHECKED);
		}

		POINT cursorPos;
		GetCursorPos(&cursorPos);
		TrackPopupMenu(mainMenu, TPM_RIGHTBUTTON, cursorPos.x, cursorPos.y, 0, hWnd, 0);
		PostMessageA(hWnd, WM_NULL, 0, 0);

		DestroyMenu(subMenu1);
		DestroyMenu(mainMenu);

		return 0;
	}

	return _window_proc(self, notUsed, wParam, uMsg, lParam);
}


//
// __window_layout
//

int __fastcall __window_layout(int self, void *notUsed, signed int width, int height)
{
	int result; // eax@1
	int v5; // edi@10
	int v6; // edi@15

	result = *(DWORD *)(self + 3232);
	if (!result)
	{
		result = *(DWORD *)(self + 2936);
		if (result)
		{
			_cwnd_move_window((self + 2904), 0, width - 25, 5, 13, 13, 1);
			_cwnd_move_window((self + 896), 0, width - 50, 5, 13, 13, 1);
			_cwnd_move_window((self + 1096), 0, width - 75, 5, 13, 13, 1);
			_cwnd_move_window((self + 1296), 0, width - 100, 5, 13, 13, 1);
			if (*(DWORD *)(self + 3136))
			{
				if (*((void**)0x525A1C))
				{
					_sub_421090((int)*((void**)0x525A1C), 0, 7, 30, width - 13, height - 100);
					if (!*((DWORD *)*((void**)0x525A1C) + 447))
						_sub_42D6E0((self + 3104), 0, 0);
				}
				_cwnd_move_window((self + 1496), 0, 7, 30, width - 13, height - 100, 1);
				_sub_42D5C0((self + 3104), 0, 7, 30, width - 13, height - 100, 1);
				_cwnd_move_window((self + 1568), 0, width - 100, height - 35, 67, 12, 1);
				_cwnd_move_window((self + 1704), 0, width - 30, height - 35, 13, 13, 1);
				if (*(DWORD *)(self + 5640) && *((signed int*)0x5254D4) < 3)
				{
					_cwnd_move_window((self + 1904), 0, width / 2 - 129, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 296), 0, width / 2 - 197, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2104), 0, width / 2 - 265, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 96), 0, width / 2 - 333, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 696), 0, width / 2 - 61, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2704), 0, width / 2 + 5, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2304), 0, width / 2 + 91, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 496), 0, width / 2 + 159, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2504), 0, width / 2 + 227, height - 50, 38, 38, 1);
					_cwnd_show_window((self + 696), 0, 5);
				}
				else
				{
					v5 = (width - 56) / 2;
					_cwnd_move_window((self + 2704), 0, v5, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2304), 0, v5 + 86, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 496), 0, v5 + 154, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2504), 0, v5 + 222, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 1904), 0, v5 - 68, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 296), 0, v5 - 136, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2104), 0, v5 - 204, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 96), 0, v5 - 272, height - 50, 38, 38, 1);
					_cwnd_show_window((self + 696), 0, 0);
				}
			}
			_sub_429CF0(*(int *)(self + 3224), 0);
			_sub_428CE0(*(int *)(self + 3228), 0);
			result = _sub_42FA80();
			if (result)
			{
				if (*(DWORD *)(self + 5640) && *((signed int*)0x5254D4) < 3)
				{
					_cwnd_move_window((self + 1904), 0, width / 2 - 129, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2104), 0, width / 2 - 197, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 696), 0, width / 2 - 61, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2704), 0, width / 2 + 5, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2304), 0, width / 2 + 91, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2504), 0, width / 2 + 159, height - 50, 38, 38, 1);
					_cwnd_show_window((self + 696), 0, 5);
				}
				else
				{
					v6 = (width - 56) / 2;
					_cwnd_move_window((self + 2704), 0, v6, height - 63, 56, 56, 1);
					_cwnd_move_window((self + 2304), 0, v6 + 86, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2504), 0, v6 + 154, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 1904), 0, v6 - 68, height - 50, 38, 38, 1);
					_cwnd_move_window((self + 2104), 0, v6 - 136, height - 50, 38, 38, 1);
					_cwnd_show_window((self + 696), 0, 0);
				}
				_cwnd_show_window((self + 296), 0, 0);
				_cwnd_show_window((self + 496), 0, 0);
				result = _cwnd_show_window((self + 96), 0, 0);
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

		DetourAttach(&(PVOID&)_window_proc, __window_proc);
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

		DetourDetach(&(PVOID&)_window_proc, __window_proc);
		DetourDetach(&(PVOID&)_window_layout, __window_layout);
		//DetourDetach(&(PVOID&)_showHideButtons, __showHideButtons);
		//DetourDetach(&(PVOID&)_sub1, __sub1);
        
		error = DetourTransactionCommit();
    }
    return TRUE;
}

