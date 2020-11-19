#pragma once

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

	explicit Polygon(const Vertex v) :
		num_of_vertexes{ 1 },
		vert{ v }
	{}

	Polygon(const size_t, const Vertex[]);

	double CenterOfGravity();

	void AddNewVertex(double, double);

	void AddNewVertex(const Vertex v) { AddNewVertex(v.x, v.y); }

	int GetNumOfVertexes() { return num_of_vertexes; }

	Vertex GetValueOfVertex(int);

	void Rotation(int, int);

	void MovingPolygon(double, double);
};