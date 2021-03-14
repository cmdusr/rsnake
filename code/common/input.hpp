#pragma once

struct InputEvent
{
	enum class ID
	{
		Up,
		Down,
		Left,
		Right
	};

	ID    id;
	float value;
};
