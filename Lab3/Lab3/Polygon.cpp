#include "Polygon.h"

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

void Polygon::AddNewVertex(double x, double y)
{
	vert[num_of_vertexes].x = x;
	vert[num_of_vertexes].y = y;

	num_of_vertexes++;
}

Vertex Polygon::GetValueOfVertex(int i)
{
	if (i < num_of_vertexes)
		return { vert[i].x, vert[i].y };

	else if (!num_of_vertexes)
		throw std::invalid_argument("There're no vertexes at all!");

	else 
		throw std::invalid_argument("There are less vertexes!");
}

void Polygon::Rotation(int angle, int pos)
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

void Polygon::MovingPolygon(double x, double y)
{
	for (int i = 0; i < num_of_vertexes; i++)
	{
		vert[i].x += x;
		vert[i].y += y;
	}
}