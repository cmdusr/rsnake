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
	x_pos = 0;
	y_pos = 0;
	tilemap[x_pos][y_pos] = Tile::Snake;
}

void RSnake::update_input()
{
	for(int i = 0; i < num_events; ++i)
	{
		switch(input_events[i].id)
		{
			default: break; // Do nothing
			case InputEvent::ID::Up:    heading = Heading::Up;    break;
			case InputEvent::ID::Down:  heading = Heading::Down;  break;
			case InputEvent::ID::Left:  heading = Heading::Left;  break;
			case InputEvent::ID::Right: heading = Heading::Right; break;
		}
	}
	rcom::zero(input_events.to_bytes());
	num_events = 0;
}

void RSnake::update_gameplay()
{
	tilemap[x_pos][y_pos] = Tile::Empty;

	// Move head
	switch(heading)
	{
		default: break; // Do nothing
		case Heading::Up:    y_pos -= 1; break;
		case Heading::Down:  y_pos += 1; break;
		case Heading::Left:  x_pos -= 1; break;
		case Heading::Right: x_pos += 1; break;
	}

	if(x_pos < 0)
	{
		x_pos = tilemap.size() - 1;
	}
	else if(x_pos >= tilemap.size())
	{
		x_pos = 0;
	}
	if(y_pos < 0)
	{
		y_pos = tilemap[0].size() - 1;
	}
	else if(y_pos >= tilemap[0].size())
	{
		y_pos = 0;
	}

	tilemap[x_pos][y_pos] = Tile::Snake;
}

void RSnake::update_screen()
{
	Quad   quad{};
	Colour colour{};

	for(size_t i = 0; i < tilemap.size(); ++i)
	{
		for(size_t j = 0; j < tilemap[0].size(); ++j)
		{
			quad.position = {i * tile_size.x, j * tile_size.y};
			quad.size     = tile_size;

			switch(tilemap[i][j])
			{
				default: // Same as Tile::Empty
				case Tile::Empty: colour = white; break;
				case Tile::Food:  colour = green; break;
				case Tile::Snake: colour = red;   break;
			}

			platform->draw_quad(quad, colour);
		}
	}
}

void RSnake::update()
{
	update_input();
	update_gameplay();
	update_screen();
}

void RSnake::inform(InputEvent event)
{
	input_events[num_events++] = event;
}
