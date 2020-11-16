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

	double CenterOfGravity();

	void AddNewVertex(double, double);

	int GetNumOfVertexes() { return num_of_vertexes; }

	Vertex GetValueOfVertex(int);

	void Rotation(int, int);

	void MovingPolygon(double, double);
};