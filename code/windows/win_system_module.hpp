#pragma once

#include "win_state_module.hpp"

namespace Windows
{
	class SystemModule : public StateModule
	{
	public:
		SystemModule(Internal&);
		void init();
		void quit();
	};
}
// namespace Windows
