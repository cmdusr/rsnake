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

	struct Position
	{
		int x;
		int y;
	};

	constexpr static const Vec2 tile_size{30, 30};
	rcom::Array<Tile, 15, 17> tilemap = {};

	Heading   heading;
	size_t head;
	size_t tail;
	rcom::Array<Position, decltype(tilemap)::flat_size()> body;

	void update_input();
	void update_gameplay();
	void update_screen();
};
