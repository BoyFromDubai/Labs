#pragma once

#include <iosfwd>

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

	Polygon(const size_t, const Vertex[]);

	explicit Polygon(const Vertex v) :
		Polygon()
	{
		AddNewVertex(v);
	}

	Polygon(const Polygon&);

	Polygon(Polygon&&);

	~Polygon() 
	{
		delete[] vert;
	}

	Polygon& operator += (Vertex v) { AddNewVertex(v); return *this; }	
	
	Polygon& operator = (Polygon&&);

	Polygon& operator = (const Polygon&);

	friend std::ostream& operator << (std::ostream&, const Polygon&);

	friend std::istream& operator >> (std::istream&, Polygon&);

	Polygon& operator () (const double x, const double y)
	{
		for (int i = 0; i < num_of_vertices; i++)
		{
			vert[i].x += x;

			vert[i].y += y;
		}

		return *this;
	}

	Polygon& operator () (const int, const int);

	const Vertex& operator [] (const int) const;

	double CenterOfGravity() const;

	void AddNewVertex(const Vertex);

	int GetNumOfVertexes() const { return num_of_vertices; }
};