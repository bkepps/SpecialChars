#include <iostream>
#include <Windows.h>

void sendKey(BYTE key) {
	keybd_event(0, key, KEYEVENTF_UNICODE, NULL);
}

int main() {
	SHORT shiftStat = 0;

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
			Sleep(500);
		}
		Sleep(100);
	}

	return 0;
}