#pragma once

#include "../../modules/game.hpp"
#include "../../rcom/array.hpp"
#include "../../common/data.hpp"

I_Game* get_game_api(GameImport);

class RSnake : public I_Game
{
public:
	RSnake(GameImport);
	RSnake() = default;
	GAME_API void init();
	GAME_API void update();
	GAME_API void inform(InputEvent);
private:
	I_Platform*                 platform;
	rcom::Array<InputEvent, 64> input_events;
	uint32_t                    num_events;

	int direction;
	Vec2 position;
};
