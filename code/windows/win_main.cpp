#include "win_main.hpp"
#include <cstring>
#include <cstdlib>
#include <cstdio>

Windows::Platform::Platform() : I_Platform{},
	core{this},
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

bool Windows::Platform::should_reload_gamelib(const GameLib& lib)
{
	return check_file_exists(lib.alt_path);
}

bool Windows::Platform::check_file_exists(const char* path)
{
	// Exists and is not a directory
	DWORD attrib = GetFileAttributes(path);
	return (attrib != INVALID_FILE_ATTRIBUTES) && !(attrib & FILE_ATTRIBUTE_DIRECTORY);
}

// Assume .path fields are valid
I_Game* Windows::Platform::load_gamelib_validpaths(GameLib& lib)
{
	if(check_file_exists(lib.alt_path))
	{
		CopyFile(lib.alt_path, lib.path, false);
		DeleteFile(lib.alt_path);
	}

	if(!check_file_exists(lib.path))
	{
		return nullptr;
	}

	lib.handle = LoadLibrary(lib.path);
	if(!lib.handle)
	{
		return nullptr;
	}

	auto get_api = (GetGameApiFunction)GetProcAddress(lib.handle, game_api_function_name);
	if(!get_api)
	{
		return nullptr;
	}
	return get_api(internal.core);
}

I_Game* Windows::Platform::load_gamelib(const char* name, GameLib& lib)
{
	// Setup paths
	memset(lib.path, 0, sizeof(lib.path));
	strcpy_s(lib.path, name);
	strcat_s(lib.path, ".dll");

	memset(lib.alt_path, 0, sizeof(lib.alt_path));
	strcpy_s(lib.alt_path, name);
	strcat_s(lib.alt_path, "_temp.dll");

	return load_gamelib_validpaths(lib);
}

void Windows::Platform::unload_gamelib(GameLib& lib)
{
	FreeLibrary(lib.handle);
}

I_Game* Windows::Platform::reload_gamelib(GameLib& lib)
{
	unload_gamelib(lib);
	return load_gamelib_validpaths(lib);
}

int Windows::Platform::main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	internal.hInstance = hInstance;
	internal.platform  = this;
	internal.core      = &core;

//	setup_console();

	core.init();

	for(;;)
	{
		core.update();
	}

	// Never reach here
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	static Windows::Platform platform{};
	return platform.main(hInstance, hPrevInstance, pCmdLine, nCmdShow);
}
