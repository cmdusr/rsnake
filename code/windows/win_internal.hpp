#pragma once

#include "../modules/game.hpp"
#include <windows.h>

namespace Windows
{
	class Internal
	{
	public:
		constexpr static const char* gamelib_path      = "game.dll";
		constexpr static const char* temp_gamelib_path = "game_temp.dll";

		HINSTANCE hInstance;

		// Game
		HMODULE gamelib;
		I_Game* game;

		class I_Platform* platform;

		// Modules
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
