#pragma once

#if defined(_WIN32)
	#include "../windows/win_platform.hpp"
	typedef Windows::Platform Platform;
#else
	#error "Undefined platform"
#endif
