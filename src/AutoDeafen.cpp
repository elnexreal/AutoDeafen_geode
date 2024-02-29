#include "AutoDeafen.hpp"

// Set default to false
bool AutoDeafen::enabled = false;

// Toggles the deafen by pressing a key combination (hardcoded ass shit)
void AutoDeafen::toggleDeafen() {
	enabled = !enabled;

	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// press the key
	ip.ki.wVk = VK_PRIOR;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	// release the key
	ip.ki.wVk = VK_PRIOR;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
