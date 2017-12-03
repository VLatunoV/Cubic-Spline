#include "cubic.h"

vec2d cubic::calc(float t)
{
	return a * (t * t * t) + b * (t * t) + c * t + d;
}