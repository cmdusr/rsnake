#pragma once

#include "../../modules/game.hpp"

I_Game* get_game_api(I_Core* core);

struct Internal
{
	I_Core* core;
};

class RSnake : public I_Game
{
public:
	GAME_API void init();
	GAME_API void update();
	void set_core(I_Core*);
private:
	Internal internal;
};
