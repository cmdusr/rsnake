#include "win_platform.hpp"
#include "win_internal.hpp"
#include "win_system.hpp"
#include <cstring>

Windows::Platform::Platform(Internal& in_internal) : Submodule{in_internal}
{
}

void Windows::Platform::quit()
{
	System& system = *internal->system;
	system.quit();
}

void Windows::Platform::refresh_game_lib(GameLib& lib)
{
	char temp_dll[MAX_PATH];
	strcpy_s(temp_dll, lib.name);
	strcat_s(temp_dll, "_temp.dll");

	WIN32_FIND_DATA find_data;
	HANDLE handle = FindFirstFile(temp_dll, &find_data);

	if(handle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if(CompareFileTime(&find_data.ftCreationTime, &lib.time) == 0)
	{
		return;
	}

	char lib_dll[MAX_PATH];
	strcpy_s(lib_dll, lib.name);
	strcat_s(lib_dll, ".dll");

	const char* lib_name = lib.name;
	close_game_lib(lib);
	CopyFile(temp_dll, lib_dll, FALSE);
	open_game_lib(lib_name, lib);
	lib.time = find_data.ftCreationTime;
}

void Windows::Platform::open_game_lib(const char* name, GameLib& lib)
{
	lib.name = name;

	// Add filename extension
	char buffer[MAX_PATH];
	strcpy_s(buffer, name);
	strcat_s(buffer, ".dll");

	lib.handle = LoadLibrary(buffer);

	// Get api
	GetGameApiFunction get_api = (GetGameApiFunction)GetProcAddress(lib.handle, game_api_function_name);
	lib.api = get_api();
}

void Windows::Platform::close_game_lib(GameLib& lib)
{
	FreeLibrary(lib.handle);
	lib = {};
}
