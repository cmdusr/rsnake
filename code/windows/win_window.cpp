#include "win_window.hpp"
#include "win_internal.hpp"
#include "../modules/platform.hpp"

Windows::Window::Window(Internal& in_internal) : Submodule{in_internal}
{
}

void Windows::Window::init()
{
	const HINSTANCE hInstance = internal->hInstance;

	// Register window class
	WNDCLASSA wc{};
	wc.lpfnWndProc   = main_window_proc;
	wc.lpszClassName = main_window_class_name;
	wc.style         = CS_OWNDC;
	wc.hInstance     = hInstance;

	HRESULT result = RegisterClassA(&wc);

	if(FAILED(result))
	{
		internal->platform->error("Failed to register window class: %s", main_window_class_name);
	}

	// Create main window
	static const char* title  = "rgame";
	static const int   width  = 800;
	static const int   height = 600;
	static const DWORD style  = WS_SYSMENU|WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE|WS_THICKFRAME;

	HWND current_window = CreateWindowExA(
		0,
		main_window_class_name,
		title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		0,
		0,
		hInstance,
		0
	);

	SetWindowLongPtrA(current_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	static_assert(sizeof(LONG_PTR) >= sizeof(void*), "Bad cast to LONG_PTR");

	internal->hWnd = current_window;
}

void Windows::Window::pump_message_queue()
{
	MSG msg;
	while(PeekMessageA(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		if(!GetMessageA(&msg, 0, 0, 0))
		{
			internal->platform->quit();
		}

		DWORD event_time = msg.time;

		TranslateMessage(&msg);
		DispatchMessageA(&msg);

		internal->event_time = event_time;
	}
}

LRESULT CALLBACK Windows::Window::main_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = (Window*)GetWindowLongPtrA(hWnd, GWLP_USERDATA);
	return window->main_window_proc_imp(hWnd, uMsg, wParam, lParam);
}

LRESULT Windows::Window::main_window_proc_imp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		default: break;

		case WM_CLOSE:
		{
			internal->platform->quit();
		}
		break;
	}
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}
