#pragma once

#include "../../modules/game.hpp"
#include "../../rcom/array.hpp"

I_Game* get_game_api(GameImport);

class RSnake : public I_Game
{
public:
	RSnake(GameImport);
	GAME_API void init();
	GAME_API void update();
	GAME_API void inform(rcom::ArrayPtr<InputEvent>);
private:
	I_Platform*                 platform;
	rcom::Array<InputEvent, 64> input_events;
	uint32_t                    num_events;
};
