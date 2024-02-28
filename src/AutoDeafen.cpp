#include "AutoDeafen.hpp"

// Set default to false
bool AutoDeafen::enabled = false;

// Toggles the deafen by pressing a key combination (hardcoded ass shit)
void AutoDeafen::toggleDeafen() {
	enabled = !enabled;

	// Simulate CTRL + LEFT SHIFT + F12 key press
	keybd_event(VK_CONTROL, 0, 0, 0); // Press down CTRL key
	keybd_event(VK_LSHIFT, 0, 0, 0);  // Press down LEFT SHIFT key
	keybd_event(VK_F12, 0, 0, 0);	  // Press down F12 key

	// Simulate CTRL + LEFT SHIFT + F12 key release
	keybd_event(VK_F12, 0, KEYEVENTF_KEYUP, 0);		// Release F12 key
	keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);	// Release LEFT SHIFT key
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // Release CTRL key
}
