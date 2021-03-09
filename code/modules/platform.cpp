#include "platform.hpp"
#include <cstdarg>

#if defined(_WIN32)
	#include "../windows/win_main.hpp"
	typedef Windows::Platform Platform;
#endif

void I_Platform::quit()
{
	return static_cast<Platform*>(this)->quit();
}

void I_Platform::error(const char* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	return static_cast<Platform*>(this)->error(fmt, argp);
}
