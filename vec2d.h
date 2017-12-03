#pragma once

struct vec2d
{
	float x, y;
};


vec2d operator- (const vec2d& lhs);
vec2d operator+ (const vec2d& lhs, const vec2d& rhs);
vec2d operator- (const vec2d& lhs, const vec2d& rhs);
vec2d operator* (const vec2d& lhs, float rhs);
vec2d operator* (float lhs, const vec2d& rhs);
vec2d operator/ (const vec2d& lhs, float rhs);
vec2d operator/ (float lhs, const vec2d& rhs);