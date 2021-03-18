#include <Windows.h>
#include <iostream>

#define IDS_TIP                         1
#define _countof(x) (sizeof(x) / sizeof((x)[0]))

void LoadStringSafe(UINT nStrID, LPTSTR szBuf, UINT nBufLen)
{
	UINT nLen = LoadString(GetModuleHandleW(NULL), nStrID, szBuf, nBufLen);
	if (nLen >= nBufLen)
		nLen = nBufLen - 1;
	szBuf[nLen] = 0;
}

void sendKey(BYTE key) {
	keybd_event(0, key, KEYEVENTF_UNICODE, NULL);
	Sleep(500);
}

int main() {
	SHORT shiftStat = 0;

	HWND consoleWnd = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(consoleWnd, &dwProcessId);
	//if (GetCurrentProcessId() == dwProcessId)
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
	//else
		//std::cout << "SpecialChars running . . ." << std::endl << "ctrl+C to exit" << std::endl << "running in console, so not hidden" << std::endl;

	GetModuleHandle(nullptr);

	PNOTIFYICONDATAW stData = new NOTIFYICONDATAW;
	ZeroMemory(stData, sizeof(stData));
	stData->cbSize = sizeof(stData);
	stData->hWnd = consoleWnd;
	stData->uFlags = NIF_ICON | NIF_TIP;
	//stData.uCallbackMessage = WM_TRAY;
	stData->hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	const char* toolTip = "Hello World!\0";
	int i = 0;
	do {
		stData->szTip[i] = toolTip[i];
	} while (toolTip[i++] != '\0');

	//toolTip = new CHAR[64];
	//toolTip = L"ASd";
	//LoadString(GetModuleHandle(NULL), 1, stData.szTip, "hi");
	//stData->szTip = &toolTip;
	//LoadStringSafe(IDS_TIP, stData->szTip, _countof(stData->szTip));

	Shell_NotifyIcon(NIM_ADD, stData);

	while (1) {
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000)) {		//CTLR and ALT pressed
			shiftStat = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
			if (GetAsyncKeyState('A') & 0x8000) {			//A key
				if (shiftStat) {							//Shift pressed
					sendKey('�');							//send key A with umlauts
				}
				else {										//Shift not pressed
					sendKey('�');							//send key a with umlauts
				}
			}
			if (GetAsyncKeyState('O') & 0x8000) {
				if (shiftStat) {
					sendKey('�');
				}
				else {
					sendKey('�');
				}
			}
			if (GetAsyncKeyState('U') & 0x8000) {
				if (shiftStat) {
					sendKey('�');
				}
				else {
					sendKey('�');
				}
			}
			if (GetAsyncKeyState('S') & 0x8000) {
				sendKey('�');
			}		
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				Shell_NotifyIcon(NIM_DELETE, stData);
				return 1;
			}
		}
		Sleep(100);
	}

	return 0;
}