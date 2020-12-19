#include "DynamicPolygon.h"
#include "..\Functions.h"

#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979323846

void Polygon::AddNewVertex(const Vertex v)
{
	if (num_of_vertices == cur_size)
	{	
		cur_size++;

		cur_size *= 2;

		Vertex* new_v = new Vertex[cur_size];

		for (int i = 0; i < num_of_vertices; i++)
			new_v[i] = vert[i];

		new_v[num_of_vertices] = v;

		delete[] vert;

		vert = new_v;

		num_of_vertices++;
	}

	else
	{
		vert[num_of_vertices] = v;

		num_of_vertices++;
	}

}

Polygon::Polygon(const size_t num, const Vertex vertices[]) :
	Polygon()
{
	for (int i = 0; i < num; i++)
		AddNewVertex(vertices[i]);
}

Polygon::Polygon(const Polygon& copy) :
	cur_size{ copy.cur_size },
	num_of_vertices{ copy.num_of_vertices },
	vert{ new Vertex[cur_size] }
{
	for (int i = 0; i < num_of_vertices; i++)
		vert[i] = copy.vert[i];
}

Polygon::Polygon(Polygon&& a) :
	cur_size{ a.cur_size },
	num_of_vertices{ a.num_of_vertices },
	vert{ a.vert }
{
	a.cur_size = 0;
	a.num_of_vertices = 0;
	a.vert = nullptr;
}

Polygon& Polygon::operator = (const Polygon& object)
{
	if (this != &object)
	{
		delete[] vert;

		cur_size = object.cur_size;

		num_of_vertices = object.num_of_vertices;

		vert = new Vertex[cur_size];

		for (int i = 0; i < num_of_vertices; i++)
			vert[i] = object.vert[i];
	}

	return *this;
}

Polygon& Polygon::operator = (Polygon&& object)
{
	Vertex* add_vert = vert;

	int add_size = cur_size,
		add_num = num_of_vertices;

	vert = object.vert;

	cur_size = object.cur_size;

	num_of_vertices = object.num_of_vertices;

	object.vert = add_vert;

	object.cur_size = add_size;

	object.num_of_vertices = add_num;

	return *this;
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
		throw std::invalid_argument("[ERROR]!");

	return vert[index];
}

Polygon& Polygon::operator() (const int angle, const int pos)
{
	if (angle < 0 || pos < 0 || pos >= num_of_vertices || angle % 90)
		throw std::invalid_argument("[ERROR]");

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