#pragma once

#include <windows.h>

namespace Windows
{
	class SystemModule;
	class WindowModule;

	class Internal
	{
	public:
		HINSTANCE     hInstance;
		SystemModule* system_module;
		WindowModule* window_module;
	};
}
// namespace Windows
