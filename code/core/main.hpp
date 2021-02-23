#pragma once

#include "../modules/game.hpp"
#include "../modules/platform.hpp"

namespace Core
{
	class Main
	{
	public:
		Main(Platform&);
		void init();
		void cleanup();
		void update();
	private:
		constexpr static const char* game_lib_name = "game";

		Platform*         platform;
		Platform::GameLib game_lib;
	};
}
// namespace Core
