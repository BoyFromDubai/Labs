#include "PolygonStatic.h"

#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979323846

Polygon::Polygon(const size_t num, const Vertex vertices[])
{
	for (int i = 0; i < num; i++)
		AddNewVertex(vertices[i]);
}

double Polygon::CenterOfGravity()
{
	double sum_of_radiuses = 0;

	for (int i = 0; i < num_of_vertexes; i++)
	{
		double lenght_of_r_vector = sqrt(pow(vert[i].x, 2) + pow(vert[i].y, 2));

		sum_of_radiuses += lenght_of_r_vector;
	}

	return sum_of_radiuses / num_of_vertexes;
}

std::ostream& operator << (std::ostream& out, const Polygon& p)
{
	for (int i = 0; i < p.num_of_vertexes; i++)
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

	std::cout << "\nNow you have " << p.GetNumOfVertexes();

	if (p.GetNumOfVertexes() == 1)
		std::cout << " vertex" << std::endl;
	else
		std::cout << " vertexes" << std::endl;

	return in;
}

Vertex Polygon::operator[](const int index)
{
	if (index < num_of_vertexes)
		return vert[index];

	else if (!num_of_vertexes)
		throw std::invalid_argument("There're no vertexes at all!");

	else
		throw std::invalid_argument("There are less vertexes!");
}

void Polygon::operator() (const int angle, const int pos)
{
	if (!(angle % 90) && pos < num_of_vertexes)
	{
		for (int i = 0; i < num_of_vertexes; i++)
		{
			if (i != pos)
			{
				Vertex point = vert[pos];

				vert[i].x = (vert[i].x - point.x) * cos(angle * PI / 180) - (vert[i].y - point.y) * sin(angle * PI / 180) + point.x;

				vert[i].y = (vert[i].x - point.x) * sin(angle * PI / 180) + (vert[i].y - point.y) * cos(angle * PI / 180) + point.y;
			}
		}
	}

	else if (angle % 90)
		throw std::invalid_argument("An angle must be a multiple of 90!");

	else
		throw std::invalid_argument("There're less vertexes");
}