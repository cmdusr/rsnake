#include "rsnake.hpp"

I_Game* get_game_api(GameImport game_import)
{
	static RSnake game{game_import};
	return &game;
}

RSnake::RSnake(GameImport game_import) :
	platform{game_import.platform}
{
}

void RSnake::init()
{
	// Do something
}

void RSnake::update()
{
	// Do something
}
