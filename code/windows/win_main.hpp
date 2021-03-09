#pragma once

#include "../modules/platform.hpp"
#include "win_internal.hpp"
#include "win_window.hpp"
#include <windows.h>

namespace Windows
{
	class Platform final : public I_Platform
	{
	public:
		Platform();

		int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

		PLATFORM_API void quit();
	private:
		Internal internal;
		Window   window;

		void load_gamelib();
		void reload_gamelib();
		bool should_reload_gamelib();

		static void setup_console();
		static bool check_file_exists(const char* path);
	};
}
// namespace Windows
