#pragma once

#include "../modules/platform.hpp"
#include "../modules/core.hpp"
#include "../modules/game.hpp"

class Core final : public I_Core
{
public:
	Core(I_Platform*);
	void init();
	void cleanup();
	void update();

	CORE_API void print_red();
	CORE_API void print_blue();
	CORE_API void quit();
private:
	const char* gamelib_name = "game";
	GameLib     gamelib;
	I_Game*     game;
	I_Platform* platform;
};
