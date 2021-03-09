#pragma once

#if defined(DLL_PLATFORM)
	#define PLATFORM_API
#else
	#define PLATFORM_API virtual
#endif

class I_Platform
{
public:
	PLATFORM_API void quit();
};
