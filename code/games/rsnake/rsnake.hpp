#pragma once

#include "../../modules/game.hpp"

I_Game* get_game_api(GameImport);

class RSnake : public I_Game
{
public:
	RSnake(GameImport);
	GAME_API void init();
	GAME_API void update();
private:
	I_Platform* platform;
};
