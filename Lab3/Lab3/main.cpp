#include "PolygonStatic.h"
#include "Functions.h"

#pragma comment (lib,"../LibPolygonStatic/Polygon.lib")

#include <iostream>

int main()
{
	Polygon p;

	int opt = 1,
		existance_of_vertices = 0;

	while (opt)
	{
		std::cout << "0) Exit" << std::endl;
		std::cout << "1) Add new vertex" << std::endl;
		
		if (existance_of_vertices)
		{
			std::cout << "2) Get value of centre of gravity of polygon" << std::endl;
			std::cout << "3) Get coordinates of the vertex" << std::endl;
			std::cout << "4) Turn around the point" << std::endl;
			std::cout << "5) Move the polygon" << std::endl;
			std::cout << "6) Get values of all vertices" << std::endl;
		}

		opt = GetNumber<int>("option", std::cin);

		if (opt == 1)
		{
			std::cin >> p;

			existance_of_vertices = 1;
		}

		else if (opt == 2 && existance_of_vertices)
		{
			std::cout << "Center of gravity value is " << p.CenterOfGravity() << std::endl;
		}

		else if (opt == 3 && existance_of_vertices)
		{
			int pos = GetNumber<int>("position", std::cin);

			try
			{
				Vertex v = p[pos];

				std::cout << "\n" << pos << " element\n" << "\nValue x is " << v.x << std::endl << "Value y is " << v.y << "\n " << std::endl;
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}
		}

		else if (opt == 4 && existance_of_vertices)
		{
			int pos = GetNumber<int>("position", std::cin),
				angle = GetNumber<int>("angle", std::cin);

			try
			{
				p(angle, pos);
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}
		}

		else if (opt == 5 && existance_of_vertices)
		{
			std::cout << "Enter values of x and y to move your polygon" << std::endl;

			double x = GetNumber<double>("value x", std::cin),
				y = GetNumber<double>("value y", std::cin);

			p(x, y);
		}

		else if (opt == 6 && existance_of_vertices)
		{
			std::cout << p;
		}

		else if (opt)
			std::cout << "\nTry another option!" << std::endl;

		std::cout << std::endl;
	}

	return 0;
}