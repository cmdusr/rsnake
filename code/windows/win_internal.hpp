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

		// Input
		rcom::Array<InputEvent, 64> input_queue;
		uint32_t queue_count;

		// Game
		HMODULE gamelib;
		I_Game* game;

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
