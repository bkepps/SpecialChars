#include <Windows.h>
#include <iostream>

#include "resource.h"

void sendKey(BYTE key) {
	keybd_event(0, key, KEYEVENTF_UNICODE, NULL);
	Sleep(500);
}

int main() {
	SHORT shiftStat = 0;

	HWND consoleWnd = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(consoleWnd, &dwProcessId);
	if (GetCurrentProcessId() == dwProcessId)
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	else
		std::cout << "SpecialChars running . . ." << std::endl << "ctrl+alt+esc to exit" << std::endl << "running in console, so not hidden" << std::endl;

	GetModuleHandle(nullptr);

	PNOTIFYICONDATAW stData = new NOTIFYICONDATAW;
	ZeroMemory(stData, sizeof(stData));
	stData->cbSize = sizeof(stData);
	stData->hWnd = consoleWnd;
	stData->uFlags = NIF_ICON | NIF_TIP;
	stData->hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	const char* toolTip = "SpecialChars is running\nLctrl+Rctrl+alt+shift to exit\0";

	int i = 0;
	do {
		stData->szTip[i] = toolTip[i];
	} while (toolTip[i++] != '\0');

	Shell_NotifyIcon(NIM_ADD, stData);

	while (1) {
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000)) {		//CTLR and ALT pressed
			shiftStat = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
			if (GetAsyncKeyState('A') & 0x8000) {			//A key
				if (shiftStat) {							//Shift pressed
					sendKey('Ä');							//send key A with umlauts
				}
				else {										//Shift not pressed
					sendKey('ä');							//send key a with umlauts
				}
			}
			if (GetAsyncKeyState('O') & 0x8000) {
				if (shiftStat) {
					sendKey('Ö');
				}
				else {
					sendKey('ö');
				}
			}
			if (GetAsyncKeyState('U') & 0x8000) {
				if (shiftStat) {
					sendKey('Ü');
				}
				else {
					sendKey('ü');
				}
			}
			if (GetAsyncKeyState('S') & 0x8000) {
				sendKey('ß');
			}		
			if ((GetAsyncKeyState(VK_RCONTROL) & 0x8000) && shiftStat && (GetAsyncKeyState(VK_LCONTROL))) {
				Shell_NotifyIcon(NIM_DELETE, stData);
				return 1;
			}
		}
		Sleep(100);
	}

	return 0;
}