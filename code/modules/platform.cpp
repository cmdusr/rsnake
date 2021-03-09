#include "platform.hpp"

#if defined(_WIN32)
	#include "../windows/win_main.hpp"
	typedef Windows::Platform Platform;
#endif

void I_Platform::quit()
{
	return static_cast<Platform*>(this)->quit();
}
