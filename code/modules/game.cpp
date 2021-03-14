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

void I_Game::inform(rcom::ArrayPtr<InputEvent> events)
{
	return static_cast<RSnake*>(this)->inform(events);
}
