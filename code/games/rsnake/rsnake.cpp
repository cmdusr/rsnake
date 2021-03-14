#include "rsnake.hpp"
#include "../../rcom/array_helpers.hpp"

I_Game* get_game_api(GameImport game_import)
{
	static RSnake game{game_import};
	return &game;
}

RSnake::RSnake(GameImport game_import) :
	platform{game_import.platform}
{
}

void RSnake::init()
{
	// Do something
}

void RSnake::update()
{
	rcom::zero(input_events.to_bytes());
	num_events = 0;
}

void RSnake::inform(rcom::ArrayPtr<InputEvent> events)
{
	rcom::copy(input_events.to_bytes(), events.to_bytes());
	num_events = events.size();
}
