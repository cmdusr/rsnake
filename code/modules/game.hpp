#pragma once

#include "../rcom/array_ptr.hpp"
#include "../common/input.hpp"

#define DLL_GAME

#if defined(DLL_GAME)
	#define GAME_API virtual
#else
	#define GAME_API
#endif

class I_Platform;
class I_Game;

struct GameImport
{
	I_Platform* platform;
};

typedef I_Game* (*GetGameApiFunction)(GameImport);
static const char* game_api_function_name = "get_game_api";

class I_Game
{
public:
	GAME_API void init();
	GAME_API void update();
	GAME_API void inform(rcom::ArrayPtr<InputEvent>);
};
