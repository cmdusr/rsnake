#include "win_window.hpp"
#include "win_internal.hpp"
#include "win_system.hpp"

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
//	RCOM_ASSERT(result, "Failed to register window class");

	// Create main window
	static const char* title  = "rgame";
	static const int   width  = 800;
	static const int   height = 600;
	static const DWORD style  = WS_SYSMENU|WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE|WS_THICKFRAME;

	current_window = CreateWindowExA(
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
}

void Windows::Window::pump_message_queue()
{
	MSG msg;
	while(PeekMessageA(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		if(!GetMessageA(&msg, 0, 0, 0))
		{
			exit(EXIT_SUCCESS);
		}

		event_time = msg.time;

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

LRESULT CALLBACK Windows::Window::main_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = (Window*)GetWindowLongPtrA(hWnd, GWLP_USERDATA);
	return window->main_window_proc_imp(hWnd, uMsg, wParam, lParam);
}

#include "win_renderer_gdi.hpp"

LRESULT Windows::Window::main_window_proc_imp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		default: break;

		case WM_CLOSE:
		{
			System& sys = *internal->system;
			sys.quit();
			return 0;
		}
		break;
	}
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

HWND Windows::Window::get_current_window() const
{
	return current_window;
}
