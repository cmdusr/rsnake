#pragma once

namespace Windows
{
	class Internal;

	class StateModule
	{
	public:
		StateModule(Internal& in_internal);
	protected:
		Internal* internal;
	};
}
// namespace Windows
