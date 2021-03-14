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
	rcom::zero(input_events.to_bytes());
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
		new_head.x = tilemap.size() - 1;
	}
	else if(new_head.x >= tilemap.size())
	{
		new_head.x = 0;
	}
	if(new_head.y < 0)
	{
		new_head.y = tilemap[0].size() - 1;
	}
	else if(new_head.y >= tilemap[0].size())
	{
		new_head.y = 0;
	}

	switch(tilemap[new_head.x][new_head.y])
	{
		case Tile::Empty:
		{
			Position pos          = new_head;
			tilemap[pos.x][pos.y] = Tile::Snake;
			head                  = (head + 1) % body.size();
			body[head]            = new_head;

			pos                   = body[tail];
			tilemap[pos.x][pos.y] = Tile::Empty;
			tail                  = (tail + 1) % body.size();
		}
		break;

		case Tile::Food:
		{
			Position pos          = new_head;
			tilemap[pos.x][pos.y] = Tile::Snake;
			head                  = (head + 1) % body.size();
			body[head]            = new_head;
		}
		break;

		case Tile::Snake:
		{
			return;
		}
		break;
	}

	// Update tilemap
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
