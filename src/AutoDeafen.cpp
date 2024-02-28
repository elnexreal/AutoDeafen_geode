#include "AutoDeafen.hpp"

// Set default to false
bool AutoDeafen::enabled = false;

// Toggles the deafen by pressing a key combination (hardcoded ass shit)
void AutoDeafen::toggleDeafen() {
	enabled = !enabled;

	// Simulate CTRL + LEFT SHIFT + F12 key press
	keybd_event(VK_CONTROL, 0, 0, 0); // Press down CTRL key
	keybd_event(VK_LSHIFT, 0, 0, 0);  // Press down LEFT SHIFT key
	keybd_event(0x44, 0, 0, 0);		  // Press down D key

	// Simulate CTRL + LEFT SHIFT + F12 key release
	keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);		// Release D key
	keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);	// Release LEFT SHIFT key
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // Release CTRL key
}
