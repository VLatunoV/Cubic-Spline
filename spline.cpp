#include "spline.h"

void Spline::add_point(const vec2d& p)
{
	points.push_back(p);
	if (points.size() > 1)
	{
		polys.push_back(cubic{});
		solve_spline();
	}
}
vec2d Spline::calc(float t)
{
	size_t intervals = polys.size();
	if (intervals == 0)
		return vec2d{};
	size_t idx = (int)(t * intervals);
	return polys[idx].calc(t * intervals - idx);
}
std::vector<vec2d>& Spline::get_inter_points()
{
	return points;
}
void Spline::solve_natural_tridiag(const std::vector<vec2d>& rhs, std::vector<vec2d>& result)
{
	/* Di = first derivative of cubic[i](0)
		| 2 1 0 0 0 ... 0 0 0 || D0 |   | 3(y1-y0) |
		| 1 4 1 0 0 ... 0 0 0 || D1 |   | 3(y2-y0) |
		| 0 1 4 1 0 ... 0 0 0 || D2 |   | 3(y3-y1) |
		| 0 0 1 4 1 ... 0 0 0 || D3 | = | 3(y4-y2) |
		| . . . . . ... . . . ||..  |   |  ......  |
		| 0 0 0 0 0 ... 1 4 1 ||Dn-1|   |3(yn-yn-2)|
		| 0 0 0 0 0 ... 0 1 2 || Dn |   |3(yn-yn-1)|

		| c0 b0 0  0  0  0 ...
		| a1 c1 b1 0  0  0 ...
		| 0  a2 c2 b2 0  0 ...
		| .. .. .. .. .. .. ..
	*/
	size_t n = rhs.size();
	std::vector<float> alpha(n - 1);
	std::vector<vec2d> beta(n - 1);

	result.resize(n);
	alpha[0] = -1.f / 2.f; // -b0 / c0
	beta[0] = rhs[0] / 2.f;
	for (size_t idx = 1; idx < n - 1; ++idx)
	{
		float denom = 4.f + alpha[idx - 1]; // ci + ai*alpha[i-1]
		alpha[idx] = -1.f / denom; // -bi/denom
		beta[idx] = (rhs[idx] - beta[idx - 1]) / denom; // (rhs[i] - ai*beta[i-1]) / denom
	}
	result[n - 1] = (rhs[n - 1] - beta[n - 2]) / (2.f + alpha[n - 2]); // cn = 2
	for (size_t idx = n - 1; idx > 0; --idx)
	{
		result[idx - 1] = alpha[idx - 1] * result[idx] + beta[idx - 1];
	}
}
void Spline::solve_spline()
{
	size_t last_idx = points.size() - 1;
	std::vector<vec2d> rhs(last_idx + 1);
	std::vector<vec2d> D;

	rhs[0] = 3 * (points[1] - points[0]);
	for (size_t idx = 1; idx < last_idx; ++idx)
	{
		rhs[idx] = 3 * (points[idx + 1] - points[idx - 1]);
	}
	rhs[last_idx] = 3 * (points[last_idx] - points[last_idx - 1]);

	solve_natural_tridiag(rhs, D);

	for (size_t idx = 0; idx < last_idx; ++idx)
	{
		vec2d dp = points[idx + 1] - points[idx];
		polys[idx].a = D[idx + 1] + D[idx] - 2 * dp;
		polys[idx].b = 3 * dp - 2 * D[idx] - D[idx + 1];
		polys[idx].c = D[idx];
		polys[idx].d = points[idx];
	}
}