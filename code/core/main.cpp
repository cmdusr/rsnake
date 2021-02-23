#include "main.hpp"

Core::Main::Main(Platform& in_platform) :
	platform{&in_platform}
{
}

void Core::Main::init()
{
	platform->open_game_lib(game_lib_name, game_lib);
	game_lib.api->init();
}

void Core::Main::cleanup()
{
	platform->close_game_lib(game_lib);
}

void Core::Main::update()
{
	platform->refresh_game_lib(game_lib);
	game_lib.api->update();
}
