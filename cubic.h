#pragma once
#include "vec2d.h"

struct cubic
{
	vec2d a, b, c, d;
	vec2d calc(float t);
};