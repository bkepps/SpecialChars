#include <iostream>
#include <Windows.h>

int main() {
	BYTE keyStatus[256];

	INPUT inputs[4];
	ZeroMemory(inputs, sizeof(inputs));

	for (;;) {
		GetKeyboardState((LPBYTE)&keyStatus);
		if (keyStatus[VK_LSHIFT] && keyStatus[VK_CONTROL] && keyStatus[VK_MENU]) {

		}
	}

	return 0;
}