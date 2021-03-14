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
	for(int i = 0; i < num_events; ++i)
	{
		switch(input_events[i].id)
		{
			default:
			{
				// Do nothing
			}
			break;

			case InputEvent::ID::Up:
			{
				direction = 0;
			}
			break;

			case InputEvent::ID::Down:
			{
				direction = 1;
			}
			break;

			case InputEvent::ID::Left:
			{
				direction = 2;
			}
			break;

			case InputEvent::ID::Right:
			{
				direction = 3;
			}
			break;
		}
	}

	static const float velocity = 0.1f;

	switch(direction)
	{
		default:
		{
			// Do nothing
		}
		break;

		// Up
		case 0:
		{
			position.y -= velocity;
		}
		break;

		// Down
		case 1:
		{
			position.y += velocity;
		}
		break;

		// Left
		case 2:
		{
			position.x -= velocity;
		}
		break;

		// Right
		case 3:
		{
			position.x += velocity;
		}
		break;
	}

	Quad quad;
	quad.position = position;
	quad.size = {100.0f, 100.0f};
	Colour colour{255, 255, 255, 255};
	platform->draw_quad(quad, colour);
}

void RSnake::inform(InputEvent event)
{
	input_events[num_events++] = event;
}
