#pragma once

class Game;

typedef Game* (*GetGameApiFunction)();
static const char* game_api_function_name = "get_game_api";

class Game
{
public:
	virtual void init()   = 0;
	virtual void update() = 0;
};
