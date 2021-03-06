#include "core.hpp"
#include <iostream>

Core::Core(I_Platform* in_platform) :
	platform{in_platform}
{
}

void Core::init()
{
	game = platform->load_gamelib(gamelib_name, gamelib);
	if(game)
	{
		game->init();
	}
}

void Core::cleanup()
{
	
}

void Core::update()
{
	if(!game)
	{
		game = platform->load_gamelib(gamelib_name, gamelib);
		game->init();
	}
	if(platform->should_reload_gamelib(gamelib))
	{
		game = platform->reload_gamelib(gamelib);
		game->init();
	}

	if(game)
	{
		game->update();
	}
}

void Core::quit()
{
	platform->quit();
}

#include <windows.h>

void Core::print_red()
{
	OutputDebugString("Red\n");
}

void Core::print_blue()
{
	OutputDebugString("Blue\n");
}
