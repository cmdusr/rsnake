#pragma once

#include "../modules/game.hpp"
#include "../rcom/array.hpp"
#include <windows.h>

namespace Windows
{
	class Internal
	{
	public:
		constexpr static const char* gamelib_path      = "game.dll";
		constexpr static const char* temp_gamelib_path = "game_temp.dll";

		HINSTANCE hInstance;

		// Window
		HWND  hWnd;
		DWORD event_time;

		// Game
		HMODULE gamelib;
		I_Game* game;

		// Rendering
		HDC     hDC;
		HDC     old_hdc;
		int     width;
		int     height;
		HBITMAP bitmap;
		HBITMAP old_bitmap;

		// Interfaces
		class I_Platform* platform;

		// Submodules
		class Window* window;
	};

	class Submodule
	{
	public:
		inline Submodule(Internal& in_internal) :
			internal{&in_internal}
		{
		}
	protected:
		Internal* internal;
	};
}
// namespace Windows
