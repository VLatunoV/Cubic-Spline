#include "cubic.h"

vec2d cubic::calc(float t)
{
	return d + t * (c + t * (b + t * a));
}