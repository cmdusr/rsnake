#include "rsnake.hpp"
#include "../../rcom/array_helpers.hpp"
#include "../../modules/platform.hpp"

I_Game* get_game_api(GameImport game_import)
{
	static RSnake game{game_import};
	return &game;
}

RSnake::RSnake(GameImport game_import) :
	RSnake()
{
	platform = game_import.platform;
}

void RSnake::init()
{
	// Do something
}

void RSnake::update()
{
	Quad quad;
	quad.position = {};
	quad.size = {100.0f, 100.0f};
	Colour colour{255, 255, 255, 255};
	platform->draw_quad(quad, colour);
}

void RSnake::inform(InputEvent event)
{
	input_events[num_events++] = event;
}
