#include "Polygon.h"
#include "Functions.h"

#pragma comment (lib,"../lib/Polygon.lib")

#include <iostream>

int main()
{
	Polygon p;

	int opt = 1,
		existance_of_vetexes = 0;

	while (opt)
	{
		std::cout << "0) Exit" << std::endl;
		std::cout << "1) Add new vertex" << std::endl;
		
		if (existance_of_vetexes)
		{
			std::cout << "2) Get value of centre of gravity of polygon" << std::endl;
			std::cout << "3) Get coordinates of the vertex" << std::endl;
			std::cout << "4) Turn around the point" << std::endl;
			std::cout << "5) Move the polygon" << std::endl;
		}

		opt = GetNumber<int>("option");

		if (opt == 1)
		{
			float x = GetNumber<float>("x value"),
				y = GetNumber<float>("y value");

			p.AddNewVertex(x, y);


			std::cout << "\nNow you have " << p.GetNumOfVertexes();

			if (p.GetNumOfVertexes() == 1)
				std::cout << " vertex" << std::endl;
			else
				std::cout << " vertexes" << std::endl;

			existance_of_vetexes = 1;
		}

		else if (opt == 2 && existance_of_vetexes)
		{
			std::cout << "Center of gravity value is " << p.CenterOfGravity() << std::endl;
		}

		else if (opt == 3 && existance_of_vetexes)
		{
			int pos = GetNumber<int>("position");

			try
			{
				auto [x, y] = p.GetValueOfVertex(pos);

				std::cout << "\n" << pos << " element\n" << "\nValue x is " << x << std::endl << "Value y is " << y << "\n " << std::endl;
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}
		}

		else if (opt == 4 && existance_of_vetexes)
		{
			int pos = GetNumber<int>("position"),
				angle = GetNumber<int>("angle");

			try
			{
				p.Rotation(angle, pos);
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}
		}

		else if (opt == 5 && existance_of_vetexes)
		{
			std::cout << "Enter values of x and y to move your polygon" << std::endl;

			float move_x = GetNumber<float>("value x"),
				move_y = GetNumber<float>("value y");

			p.MovingPolygon(move_x, move_y);
		}

		else if (opt)
			std::cout << "\nTry another option!" << std::endl;

		std::cout << std::endl;
	}


	return 0;
}