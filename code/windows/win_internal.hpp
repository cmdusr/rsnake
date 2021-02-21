#pragma once

#include <windows.h>

namespace Windows
{
	class Internal
	{
	public:
		HINSTANCE hInstance;

		// Modules
		class System*      system;
		class Window*      window;
		class GDIRenderer* gdi_renderer;
	};
}
// namespace Windows
