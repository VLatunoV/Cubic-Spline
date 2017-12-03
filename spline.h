#pragma once
#include <vector>
#include "vec2d.h"
#include "cubic.h"

class Spline
{
	std::vector<vec2d> points;
	std::vector<cubic> polys;
	void solve_natural_tridiag(const std::vector<vec2d>& rhs, std::vector<vec2d>& result);
public:
	Spline() = default;
	~Spline() = default;
	void add_point(const vec2d& p);
	void solve_spline();
	vec2d calc(float t);
	std::vector<vec2d>& get_inter_points();
};