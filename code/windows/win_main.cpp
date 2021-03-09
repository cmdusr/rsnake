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


void Windows::Platform::error(const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	fputc('\n', stderr);
	abort();
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
		error("Could not find gamelib.");
	}

	HMODULE handle = LoadLibrary(path);
	if(!handle)
	{
		error("Failed to load gamelib");
	}

	auto get_api = (GetGameApiFunction)GetProcAddress(handle, game_api_function_name);
	if(!get_api)
	{
		error("Failed to find gamelib api function");
	}

	GameImport game_import{};
	game_import.platform = this;

	I_Game* game = get_api(game_import);
	if(!game)
	{
		error("Failed to get gamelib api");
	}

	internal.gamelib = handle;
	internal.game    = game;
}

void Windows::Platform::refresh_gamelib()
{
	const char* path      = internal.gamelib_path;
	const char* temp_path = internal.temp_gamelib_path;
	HMODULE     gamelib   = internal.gamelib;

	// Should we reload gamelib?
	if(!check_file_exists(temp_path))
	{
		return;
	}

	FreeLibrary(gamelib);
	CopyFile(temp_path, path, false);
	DeleteFile(temp_path);
	load_gamelib();
	internal.game->init();
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

		refresh_gamelib();
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
