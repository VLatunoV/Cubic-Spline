#include "vec2d.h"

vec2d operator- (const vec2d& lhs)
{
	return vec2d{ -lhs.x , -lhs.y };
}
vec2d operator+ (const vec2d& lhs, const vec2d& rhs)
{
	return vec2d{ lhs.x + rhs.x, lhs.y + rhs.y };
}
vec2d operator- (const vec2d& lhs, const vec2d& rhs)
{
	return vec2d{ lhs.x - rhs.x, lhs.y - rhs.y };
}
vec2d operator* (const vec2d& lhs, float rhs)
{
	return vec2d{ lhs.x * rhs, lhs.y * rhs };
}
vec2d operator* (float lhs, const vec2d& rhs)
{
	return rhs * lhs;
}
vec2d operator/ (const vec2d& lhs, float rhs)
{
	return lhs * (1 / rhs);
}
vec2d operator/ (float lhs, const vec2d& rhs)
{
	return rhs / lhs;
}