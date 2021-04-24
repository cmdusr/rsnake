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
		PLATFORM_API void error(const char* fmt, ...);
		PLATFORM_API void draw_quad(Quad, Colour);
		PLATFORM_API void draw_text(const char* text, Vec2 pos, Colour colour);

		void recompile_game_dll();
	private:
		Internal internal;
		Window   window;

		void init_gamelib();
		void load_gamelib();
		void refresh_gamelib();

		void begin_rendering();
		void end_rendering();

		static void setup_console();
		static bool check_file_exists(const char* path);
	};
}
// namespace Windows
