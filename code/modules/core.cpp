#include "core.hpp"
#include "../core/core.hpp"

void I_Core::quit()
{
	return static_cast<Core*>(this)->quit();
}

void I_Core::print_red()
{
	return static_cast<Core*>(this)->print_red();
}

void I_Core::print_blue()
{
	return static_cast<Core*>(this)->print_blue();
}
