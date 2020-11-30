#include "StaticPolygon.h"
#include "..\Functions.h"

#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979323846

Polygon::Polygon(const size_t num, const Vertex vertices[]) : Polygon()
{
	if (num >= num_of_vertices || num < 0)
		throw std::invalid_argument("Invalid index!");

	for (int i = 0; i < num; i++)
		AddNewVertex(vertices[i]);
}

double Polygon::CenterOfGravity() const
{
	double sum_of_radiuses = 0;

	for (int i = 0; i < num_of_vertices; i++)
	{
		double lenght_of_r_vector = sqrt(pow(vert[i].x, 2) + pow(vert[i].y, 2));

		sum_of_radiuses += lenght_of_r_vector;
	}

	return sum_of_radiuses / num_of_vertices;
}

std::ostream& operator << (std::ostream& out, const Polygon& p)
{
	for (int i = 0; i < p.num_of_vertices; i++)
	{
		out << "Values of " << i << " point: ";
		out << p.vert[i].x << ", " << p.vert[i].y << std::endl;
	}

	return out;
}

std::istream& operator >> (std::istream& in, Polygon& p)
{
	Vertex v;

	v.x = GetNumber<float>("x value", in);
	v.y = GetNumber<float>("y value", in);

	p += v;

	return in;
}

const Vertex& Polygon::operator[](const int index) const
{
	if (index < 0 || index >= num_of_vertices)
		throw std::invalid_argument("Invalid index!");

	return vert[index];
}

Polygon& Polygon::operator() (const int angle, const int pos)
{
	if (angle < 0 || pos < 0 || pos >= num_of_vertices || angle % 90)
		throw std::invalid_argument("Try again enter new values!");

	for (int i = 0; i < num_of_vertices; i++)
	{
		if (i != pos)
		{
			Vertex point = vert[pos];

			vert[i].x = (vert[i].x - point.x) * cos(angle * PI / 180) - (vert[i].y - point.y) * sin(angle * PI / 180) + point.x;

			vert[i].y = (vert[i].x - point.x) * sin(angle * PI / 180) + (vert[i].y - point.y) * cos(angle * PI / 180) + point.y;
		}
	}

	return *this;
}