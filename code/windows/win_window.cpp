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

		case WM_KEYDOWN:
		{
			handle_key_event(hWnd, uMsg, wParam, lParam);
		}
		break;
	}
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

void Windows::Window::handle_key_event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto add_event = [this](const InputEvent& event)
	{
		internal->input_queue[internal->queue_count++] = event;
	};

	switch(wParam)
	{
		default:
		{
			// Do nothing
		}
		break;

		case VK_ESCAPE:
		{
			internal->platform->quit();
		}
		break;

		case 'W':
		case VK_UP:
		{
			InputEvent event;
			event.id    = InputEvent::ID::Up;
			event.value = 1.0f;
			add_event(event);
		}
		break;

		case 'S':
		case VK_DOWN:
		{
			InputEvent event;
			event.id    = InputEvent::ID::Down;
			event.value = 1.0f;
			add_event(event);
		};
		break;

		case 'A':
		case VK_LEFT:
		{
			InputEvent event;
			event.id    = InputEvent::ID::Left;
			event.value = 1.0f;
			add_event(event);
		};
		break;

		case 'D':
		case VK_RIGHT:
		{
			InputEvent event;
			event.id    = InputEvent::ID::Right;
			event.value = 1.0f;
			add_event(event);
		};
		break;
	}
}
