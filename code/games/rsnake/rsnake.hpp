#pragma once

#include "../../modules/game.hpp"
#include "../../common/data.hpp"

I_Game* get_game_api(GameImport);

template<typename T, size_t N> constexpr size_t array_size(const T(&)[N])
{
	return N;
}

template<typename T, size_t N1, size_t N2> constexpr size_t flat_size(const T(&)[N1][N2])
{
	return N1 * N2;
}

template<typename T, size_t N1, size_t N2> constexpr size_t array_size_1(const T(&)[N1][N2])
{
	return N1;
}

template<typename T, size_t N1, size_t N2> constexpr size_t array_size_2(const T(&)[N1][N2])
{
	return N2;
}

template<typename T, size_t N> constexpr size_t byte_size(const T(&t)[N])
{
	return sizeof(T) * array_size(t);
}

template<typename T, size_t N1, size_t N2> constexpr size_t byte_size(const T(&t)[N1][N2])
{
	return sizeof(T) * array_size(t);
}

class RSnake : public I_Game
{
public:
	RSnake(GameImport);
	RSnake() = default;
	GAME_API void init();
	GAME_API void update();
	GAME_API void inform(InputEvent);
private:
	I_Platform* platform;
	InputEvent  input_events[64];
	uint32_t    num_events;

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

	Tile tilemap[17][15];

	Position body[sizeof(tilemap) / sizeof(Tile)];
	Heading heading;
	size_t  head;
	size_t  tail;
	int     score;

	void reset();
	void update_input();
	void update_gameplay();
	void update_screen();
	void new_food();
};
