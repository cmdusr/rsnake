#pragma once

#include <windows.h>

class I_Game;

namespace Windows
{
	struct GameLib
	{
		HMODULE handle;
		I_Game* api;
		char    path[MAX_PATH];
		char    alt_path[MAX_PATH];
	};
}
// namespace Windows
