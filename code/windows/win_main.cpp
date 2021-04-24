#include "win_main.hpp"
#include "../modules/game.hpp"
#include <cstring>
#include <cstdlib>
#include <cstdio>

Windows::Platform::Platform() : I_Platform{},
internal{},
window{ internal }
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
	freopen_s(&temp, "CONIN$", "r", stdin);
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

void Windows::Platform::init_gamelib()
{
	const char* path      = internal.gamelib_path;
	const char* temp_path = internal.temp_gamelib_path;
	HMODULE     gamelib   = internal.gamelib;

	if(check_file_exists(temp_path))
	{
		CopyFile(temp_path, path, false);
		DeleteFile(temp_path);
	}

	load_gamelib();
	internal.game->init();
}

void Windows::Platform::begin_rendering()
{
	// Make all draw commands to hdc
	// Copy to real_hdc at end of drawing

	HWND hWnd    = internal.hWnd;
	HDC  old_hdc = GetDC(hWnd);
	HDC  hDC     = CreateCompatibleDC(internal.old_hdc);

	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width  = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HBITMAP bitmap     = CreateCompatibleBitmap(old_hdc, width, height);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(hDC, bitmap);

	internal.old_hdc    = old_hdc;
	internal.hDC        = hDC;
	internal.width      = width;
	internal.height     = height;
	internal.bitmap     = bitmap;
	internal.old_bitmap = old_bitmap;
}

void Windows::Platform::end_rendering()
{
	HWND hWnd          = internal.hWnd;
	HDC hDC            = internal.hDC;
	HDC old_hdc        = internal.old_hdc;
	int width          = internal.width;
	int height         = internal.height;
	HBITMAP bitmap     = internal.bitmap;
	HBITMAP old_bitmap = internal.old_bitmap;

	BitBlt(old_hdc, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
	SelectObject(old_hdc, hDC);
	SelectObject(old_hdc, old_bitmap);

	DeleteObject(bitmap);
	DeleteDC(hDC);
	ReleaseDC(hWnd, old_hdc);
}

void Windows::Platform::draw_quad(Quad quad, Colour colour)
{
	// Convert to rect
	RECT rect;
	rect.left   = quad.position.x;
	rect.bottom = quad.position.y;
	rect.right  = quad.position.x + quad.size.x;
	rect.top    = quad.position.y + quad.size.y;

	// Set colour brush
	HBRUSH hBrush = CreateSolidBrush(RGB(colour.r, colour.g, colour.b));
	auto temp = SelectObject(internal.hDC, hBrush);

	// Draw rectangle
	Rectangle(internal.hDC, rect.left, rect.top, rect.right, rect.bottom);

	// Restore
	SelectObject(internal.hDC, temp);

	// Cleanup
	DeleteObject(hBrush);
}

void Windows::Platform::draw_text(const char* text, Vec2 pos, Colour colour)
{
	const HDC hDC   = internal.hDC;
	const HWND hWnd = internal.hWnd;

	SetTextColor(hDC, RGB(colour.r, colour.g, colour.b));
	SetBkMode(hDC, TRANSPARENT);

	RECT rect;
	GetClientRect(hWnd, &rect);
	rect.left = pos.x;
	rect.top  = pos.y;

	DrawText(hDC, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
}

void Windows::Platform::recompile_game_dll()
{
	ShellExecuteA(internal.hWnd, "open", "build.bat", nullptr, "..\\", 0);
}

int Windows::Platform::main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	internal.hInstance = hInstance;
	internal.platform  = this;
	internal.window    = &window;

	window.init();

	init_gamelib();

	for(;;)
	{
		window.pump_message_queue();
		refresh_gamelib();
		begin_rendering();
		internal.game->update();
		end_rendering();
		Sleep(100);
	}

	// Never reach here
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	static Windows::Platform platform{};
	return platform.main(hInstance, hPrevInstance, pCmdLine, nCmdShow);
}
