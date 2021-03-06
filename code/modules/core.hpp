#pragma once

#include "../common/data.hpp"

#if defined(DLL_CORE)
	#define CORE_API
#else
	#define CORE_API virtual
#endif

class I_Core
{
public:
	CORE_API void quit();
	CORE_API void print_red();
	CORE_API void print_blue();
};
