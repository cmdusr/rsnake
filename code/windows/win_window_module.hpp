#pragma once

#include "win_state_module.hpp"
#include <windows.h>

namespace Windows
{
	class WindowModule : public StateModule
	{
	public:
		WindowModule(Internal&);
		void init();
		void pump_message_queue();
	private:
		static constexpr const char* main_window_class_name = "main_window_class";

		DWORD event_time;
		HWND  current_window;

		static LRESULT CALLBACK main_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT main_window_proc_imp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
// namespace Windows

