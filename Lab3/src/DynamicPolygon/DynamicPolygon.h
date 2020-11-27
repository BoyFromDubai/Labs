#pragma once
#include "..\Functions.h"

struct Vertex
{
	double x,
		y;
};

class Polygon
{
private:
	int num_of_vertices,
		cur_size;

	Vertex* vert;

public:

	Polygon() :
		num_of_vertices{},
		cur_size{},
		vert{}
	{}

	~Polygon() 
	{
		delete[] vert;
	}

	void operator += (Vertex);

	/*explicit Polygon(const Vertex v) :
		num_of_vertices{ 1 },
		vert{ v }
	{}*/

	friend std::ostream& operator << (std::ostream&, const Polygon&);

	friend std::istream& operator >> (std::istream&, Polygon&);

	void operator () (const double x, const double y)
	{
		for (int i = 0; i < num_of_vertices; i++)
		{
			vert[i].x += x;
			vert[i].y += y;
		}
	}

	void operator () (const int, const int);

	Vertex operator [] (const int);

	Polygon(const size_t, const Vertex[]);

	double CenterOfGravity();

	void AddNewVertex(const Vertex);

	int GetNumOfVertexes() { return num_of_vertices; }
};