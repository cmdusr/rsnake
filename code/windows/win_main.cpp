#include "win_main.hpp"
#include "../modules/game.hpp"
#include <cstring>
#include <cstdlib>
#include <cstdio>

Windows::Platform::Platform() : I_Platform{},
	internal{},
	window{internal}
{
}

void Windows::Platform::quit()
{
	std::quick_exit(EXIT_SUCCESS);
}

void Windows::Platform::setup_console()
{
	FILE* temp;
	AllocConsole();
	freopen_s(&temp, "CONIN$",  "r", stdin);
	freopen_s(&temp, "CONOUT$", "w", stdout);
	freopen_s(&temp, "CONOUT$", "w", stderr);
}

bool Windows::Platform::check_file_exists(const char* path)
{
	// Exists and is not a directory
	DWORD attrib = GetFileAttributes(path);
	return (attrib != INVALID_FILE_ATTRIBUTES) && !(attrib & FILE_ATTRIBUTE_DIRECTORY);
}

// GameLib path fields must be valid
void Windows::Platform::load_gamelib()
{
	const char* path = internal.gamelib_path;

	if(!check_file_exists(path))
	{
		// error
		return;
	}

	HMODULE handle = LoadLibrary(path);
	if(!handle)
	{
		// error
		return;
	}

	auto get_api = (GetGameApiFunction)GetProcAddress(handle, game_api_function_name);
	if(!get_api)
	{
		// error
		return;
	}

	GameImport game_import{};
	game_import.platform = this;

	I_Game* game = get_api(game_import);
	if(!game)
	{
		// Error
		return;
	}

	internal.gamelib = handle;
	internal.game    = game;
}

bool Windows::Platform::should_reload_gamelib()
{
	return check_file_exists(internal.temp_gamelib_path);
}

void Windows::Platform::reload_gamelib()
{
	const char* path      = internal.gamelib_path;
	const char* temp_path = internal.temp_gamelib_path;
	HMODULE     gamelib   = internal.gamelib;

	if(!check_file_exists(temp_path))
	{
		// Error
		return;
	}

	FreeLibrary(gamelib);
	CopyFile(temp_path, path, false);
	DeleteFile(temp_path);
	load_gamelib();
}

int Windows::Platform::main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	internal.hInstance = hInstance;
	internal.platform  = this;
	internal.window    = &window;
	internal.gamelib   = nullptr;
	internal.game      = nullptr;

	window.init();

	// Setup GameLib
	load_gamelib();
	internal.game->init();

	for(;;)
	{
		window.pump_message_queue();

		if(should_reload_gamelib())
		{
			reload_gamelib();
			internal.game->init();
		}
		internal.game->update();
	}

	// Never reach here
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	static Windows::Platform platform{};
	return platform.main(hInstance, hPrevInstance, pCmdLine, nCmdShow);
}
