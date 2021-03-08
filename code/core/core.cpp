#include "core.hpp"
#include <iostream>

Core::Core(I_Platform* in_platform) :
	platform{in_platform}
{
}

void Core::init()
{
	game = platform->load_gamelib(gamelib_name, gamelib);
	game->init();
}

void Core::cleanup()
{
	
}

void Core::update()
{
	if(platform->should_reload_gamelib(gamelib))
	{
		game = platform->reload_gamelib(gamelib);
		game->init();
	}

	game->update();
}

void Core::quit()
{
	platform->quit();
}
