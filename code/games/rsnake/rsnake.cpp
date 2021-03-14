#include "rsnake.hpp"
#include "../../modules/platform.hpp"
#include <cstring>

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
	head = 0;
	tail = 0;
	body[head].x = 5;
	body[head].y = 5;

	tilemap[8][5] = Tile::Food;
	tilemap[8][6] = Tile::Food;
	tilemap[8][8] = Tile::Food;
	tilemap[8][9] = Tile::Food;
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

	memset(input_events, 0, byte_size(input_events));
	num_events = 0;
}

void RSnake::update_gameplay()
{
	Position new_head = body[head];

	// Move head
	switch(heading)
	{
		default: break; // Do nothing
		case Heading::Up:    new_head.y -= 1; break;
		case Heading::Down:  new_head.y += 1; break;
		case Heading::Left:  new_head.x -= 1; break;
		case Heading::Right: new_head.x += 1; break;
	}

	// Handle edges
	if(new_head.x < 0)
	{
		new_head.x = array_size_1(tilemap) - 1;
	}
	else if(new_head.x >= array_size_1(tilemap))
	{
		new_head.x = 0;
	}
	if(new_head.y < 0)
	{
		new_head.y = array_size_2(tilemap) - 1;
	}
	else if(new_head.y >= array_size_2(tilemap))
	{
		new_head.y = 0;
	}

	switch(tilemap[new_head.x][new_head.y])
	{
		case Tile::Empty:
		{
			// Advance head in the queue
			head       = (head + 1) % array_size(body);
			body[head] = new_head;

			// New head tile is part of the snake
			tilemap[new_head.x][new_head.y] = Tile::Snake;

			// Tail tile is no longer part of the snake
			Position tail_pos               = body[tail];
			tilemap[tail_pos.x][tail_pos.y] = Tile::Empty;

			// Advance tail in the queue
			tail = (tail + 1) % array_size(body);
		}
		break;

		case Tile::Food:
		{
			// Advance head in the queue
			head       = (head + 1) % array_size(body);
			body[head] = new_head;

			// New head tile is part of the snake
			tilemap[new_head.x][new_head.y] = Tile::Snake;

			// Don't remove / advance tail -> Grows snake by 1
		}
		break;

		case Tile::Snake:
		{
			// TODO: Handle death
			return;
		}
		break;
	}
}

void RSnake::update_screen()
{
	Quad   quad{};
	Colour colour{};

	for(size_t i = 0; i < array_size_1(tilemap); ++i)
	{
		for(size_t j = 0; j < array_size_2(tilemap); ++j)
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
