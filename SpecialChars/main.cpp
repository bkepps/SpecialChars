#include <iostream>
#include <Windows.h>

int main() {
	UINT error;

	INPUT inputs[7];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;
	inputs[0].ki.wScan = 0x00C4;	//A with umlauts

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.dwFlags = KEYEVENTF_UNICODE;
	inputs[1].ki.wScan = 0x00E4;	//a with umlauts


	while (1) {
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000)) {		//CTLR and ALT pressed
			if (GetAsyncKeyState(0x41) & 0x8000) {								//A key
				if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {						//Shift pressed
					error = SendInput(1, &inputs[0], sizeof(INPUT));
					std::cout << std::hex << error;
				}
				else {															//Shift not pressed
					SendInput(1, &inputs[1], sizeof(INPUT));
				}
			}
			Sleep(500);
		}
	}

	return 0;
}