#pragma once

#include "../common/data.hpp"

#if defined(DLL_PLATFORM)
	#define PLATFORM_API
#else
	#define PLATFORM_API virtual
#endif

class I_Platform
{
public:
	PLATFORM_API void quit();
	PLATFORM_API void error(const char* fmt, ...);
	PLATFORM_API void draw_quad(Quad, Colour);
	PLATFORM_API void draw_text(const char* text, Vec2 pos, Colour colour);
};
