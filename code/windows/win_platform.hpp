#pragma once

#include "win_submodule.hpp"
#include "../modules/game.hpp"
#include <windows.h>

namespace Windows
{
	class Platform : public Submodule
	{
	public:
		struct GameLib
		{
			const char* name;
			HMODULE     handle;
			FILETIME    time;
			Game*       api;
		};

		Platform(Internal&);
		void quit();
		void open_game_lib(const char* name, GameLib&);
		void close_game_lib(GameLib&);
		void refresh_game_lib(GameLib&);
	private:
	};
}
// namespace Windows
