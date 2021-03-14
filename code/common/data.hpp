#pragma once

struct Vec2
{
	float x;
	float y;
};

struct Colour
{
	float r;
	float g;
	float b;
	float a;
};

struct Quad
{
	Vec2 position;
	Vec2 size;
};

static const Colour black = {000, 000, 000, 255};
static const Colour white = {255, 255, 255, 255};
static const Colour red   = {255, 000, 000, 255};
static const Colour green = {000, 255, 000, 255};
static const Colour blue  = {000, 000, 255, 255};
