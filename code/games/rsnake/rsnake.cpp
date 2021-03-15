#include "rsnake.hpp"
#include "../../modules/platform.hpp"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>

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
	srand(time(NULL));
	reset();
}

void RSnake::reset()
{
	score = 0;

	for(size_t i = 0; i < array_size_1(tilemap); ++i)
	{
		for(size_t j = 0; j < array_size_2(tilemap); ++j)
		{
			tilemap[i][j] = Tile::Empty;
		}
	}

	heading = Heading::Right;
	head = 0;
	tail = 0;
	body[head].x = 5;
	body[head].y = 5;

	head++;
	body[head].x = 6;
	body[head].y = 5;

	head++;
	body[head].x = 7;
	body[head].y = 5;

	head++;
	body[head].x = 8;
	body[head].y = 5;

	for(size_t i = 0; i <= head; ++i)
	{
		Position pos = body[i];
		tilemap[pos.x][pos.y] = Tile::Snake;
	}

	new_food();
}

void RSnake::new_food()
{
	size_t r = rand() % flat_size(tilemap);
	Position pos;
	do
	{
		pos.x = r % array_size_1(tilemap);
		pos.y = r / array_size_2(tilemap);
		r = (r + 1) % flat_size(tilemap);
	}
	while(tilemap[pos.x][pos.y] != Tile::Empty);

	tilemap[pos.x][pos.y] = Tile::Food;
}

void RSnake::update_input()
{
	for(int i = 0; i < num_events; ++i)
	{
		switch(input_events[i].id)
		{
			default: break; // Do nothing
			case InputEvent::ID::Up:
			{
				if(heading != Heading::Down)
				{
					heading = Heading::Up;
				}
			}
			break;

			case InputEvent::ID::Down:
			{
				if(heading != Heading::Up)
				{
					heading = Heading::Down;
				}
			}
			break;

			case InputEvent::ID::Left:
			{
				if(heading != Heading::Right)
				{
					heading = Heading::Left;
				}
			}
			break;

			case InputEvent::ID::Right:
			{
				if(heading != Heading::Left)
				{
					heading = Heading::Right;
				}
			}
			break;
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

#if 0
	// Handle edges
	if(new_head.x < 0)
	{
		reset();
		return;
	}
	else if(new_head.x >= array_size_1(tilemap))
	{
		reset();
		return;
	}
	if(new_head.y < 0)
	{
		reset();
		return;
	}
	else if(new_head.y >= array_size_2(tilemap))
	{
		reset();
		return;
	}
#else
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
#endif

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
			
			new_food();
			score++;
		}
		break;

		case Tile::Snake:
		{
			reset();
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

	char buffer[128];
	sprintf(buffer, "Score: %i\n", score);
	platform->draw_text(buffer, {00.0f, 00.0f}, red);
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
