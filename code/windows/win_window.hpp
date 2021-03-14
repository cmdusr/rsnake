#pragma once

#include "win_internal.hpp"
#include <windows.h>

namespace Windows
{
	class Window : public Submodule
	{
	public:
		Window(Internal&);
		void init();
		void pump_message_queue();
	private:
		static constexpr const char* main_window_class_name = "main_window_class";

		static LRESULT CALLBACK main_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT main_window_proc_imp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void handle_key_event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}
// namespace Windows
