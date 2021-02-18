#include <windows.h>
#include "win_internal.hpp"
#include "win_window_module.hpp"
#include "win_system_module.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Windows stuff
	static Windows::Internal internal{};

	// Modules
	static Windows::SystemModule system_module{internal};
	static Windows::WindowModule window_module{internal};

	// Initialise internal
	internal.hInstance     = hInstance;
	internal.system_module = &system_module;
	internal.window_module = &window_module;

	// Initialise modules
	system_module.init();
	window_module.init();

	// Main Loop
	for(;;)
	{
		window_module.pump_message_queue();
	}
}
