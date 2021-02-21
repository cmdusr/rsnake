#include <windows.h>
#include "win_internal.hpp"
#include "win_window.hpp"
#include "win_system.hpp"
#include "win_renderer_gdi.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Windows stuff
	static Windows::Internal internal{};

	// Modules
	static Windows::System      system{internal};
	static Windows::Window      window{internal};
	static Windows::GDIRenderer gdi_renderer{internal};

	// Initialise internal
	internal.hInstance    = hInstance;
	internal.system       = &system;
	internal.window       = &window;
	internal.gdi_renderer = &gdi_renderer;

	// Initialise modules
	system.init();
	window.init();
	gdi_renderer.init();

	// Main Loop
	for(;;)
	{
		window.pump_message_queue();
	}
}
