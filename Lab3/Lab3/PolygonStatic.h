#pragma once
#include "Functions.h"
#define SIZE 1000

struct Vertex
{
	double x,
		  y;
};

class Polygon
{
private:
	int num_of_vertexes;

	Vertex vert[SIZE];

public:

	Polygon() :
		num_of_vertexes{},
		vert{}
	{}

	void operator += (Vertex v)
	{
		vert[num_of_vertexes] = v;

		num_of_vertexes++;
	}

	explicit Polygon(const Vertex v) :
		num_of_vertexes{ 1 },
		vert{ v }
	{}

	friend std::ostream& operator << (std::ostream&, const Polygon&);

	friend std::istream& operator >> (std::istream&, Polygon&);

	void operator () (const double x, const double y)
	{
		for (int i = 0; i < num_of_vertexes; i++)
		{
			vert[i].x += x;
			vert[i].y += y;
		}
	}

	void operator () (const int, const int);

	Vertex operator [] (const int);

	Polygon(const size_t, const Vertex[]);

	double CenterOfGravity();

	void AddNewVertex(const Vertex v)
	{
		vert[num_of_vertexes] = v;

		num_of_vertexes++;
	}

	int GetNumOfVertexes() { return num_of_vertexes; }
};