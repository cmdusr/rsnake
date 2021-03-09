#include "game.hpp"
#include "../games/rsnake/rsnake.hpp"

void I_Game::init()
{
	return static_cast<RSnake*>(this)->init();
}

void I_Game::update()
{
	return static_cast<RSnake*>(this)->update();
}
