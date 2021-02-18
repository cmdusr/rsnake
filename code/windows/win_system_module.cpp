#include "win_system_module.hpp"
#include <windows.h>

Windows::SystemModule::SystemModule(Internal& internal) : StateModule{internal}
{

}

void Windows::SystemModule::init()
{
}

void Windows::SystemModule::quit()
{
	quick_exit(EXIT_SUCCESS);
}
