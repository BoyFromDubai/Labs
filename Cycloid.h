#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

#include <cmath>

inline double deg2rad(const double deg)
{
	return deg * M_PI / 180;
}

struct Point
{
	double x,
		   y;
};

class Cycloid
{
private:
	double r;

public:
	Cycloid() :
		r{}
	{}

	void SetR(const double);

	Point GetCoords(const double) const;

	double GetR() const { return r; }

	double GetFullSquare() const { return 3 * M_PI * r * r; }

	double GetRadiusOfCurvature(const double t) const { return 4 * r * std::sin(deg2rad(t / 2)); }

	double GetLenght(const double t) const { return 4 * r * (1 - std::cos(t / 2));}

	double GetSurfaceSquare() const { return 64 / 3 * M_PI * r * r; }

	double GetV() const { return 5 * M_PI * r * r * r; }
};


