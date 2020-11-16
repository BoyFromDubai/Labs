#include "Cycloid.h"

#include <stdexcept>

void Cycloid::SetR(const double radius)
{
	if (radius < 0)
		throw std::invalid_argument("Radius must be a positive value!");

	r = radius;
}

Point Cycloid::GetCoords(const double t) const
{
	double y = r - r * std::cos(deg2rad(t));

	return { r * std::acos((r - y) / r) - std::sqrt(2 * r * y - y * y), y };
}