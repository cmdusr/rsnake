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

	enum class Heading
	{
		Up,
		Down,
		Left,
		Right
	};

	enum class Tile
	{
		Empty = 0,
		Snake,
		Food
	};

	constexpr static const Vec2 tile_size{30, 30};

	Heading heading;
	int x_pos;
	int y_pos;

	rcom::Array<Tile, 15, 17> tilemap = {};

	void update_input();
	void update_gameplay();
	void update_screen();
};
