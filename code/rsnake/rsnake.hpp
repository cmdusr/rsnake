#pragma once

#include "../modules/game.hpp"

extern "C" Game* get_game_api();

class RSnake : public Game
{
public:
	virtual void init()   override;
	virtual void update() override;
};
