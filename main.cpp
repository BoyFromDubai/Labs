#include "../2labLib/Cycloid.h"

#include "HFunctions.h"


int main()
{
	Cycloid c;

	int opt = 1,
		existance_of_data = 0;

	while (opt)
	{
		std::cout << "0) Exit" << std::endl;

		if (!existance_of_data)
		{
			std::cout << "1) Add data of Cycloid" << std::endl;
		}
		
		else
		{
			std::cout << "1) Change data of Cycloid" << std::endl;
			std::cout << "2) Get coordinates of Cycloid" << std::endl;
			std::cout << "3) Get radius of curvature of Cycloid" << std::endl;
			std::cout << "4) Get lenght of Cycloid" << std::endl;
			std::cout << "5) Get full square of Cycloid" << std::endl;
			std::cout << "6) Get surface square of Cycloid" << std::endl;
			std::cout << "7) Get volume of Cycloid \n> ";
		}

		opt = GetNumber<int>("Option");

		if (opt == 1)
		{
			existance_of_data = 1;

			try
			{
				c.SetR(GetNumber<double>("Radius"));
			}

			catch (const std::invalid_argument& a)
			{
				std::cerr << "[ERROR] " << a.what() << std::endl;

				existance_of_data = 0;
			}

		}

		else if (opt == 2 && existance_of_data)
		{
			auto [x, y] = c.GetCoords(GetNumber<double>("t"));

			std::cout << "\nx = " << x << std::endl;
			
			std::cout << "y = " << y << std::endl;
		}

		else if (opt == 3 && existance_of_data)
		{
			double t = GetNumber<double>("t");

			std::cout << "\nRadius of Curvature = " << c.GetRadiusOfCurvature(t) << std::endl;
		}

		else if (opt == 4 && existance_of_data)
		{
			double t = GetNumber<double>("t");

			std::cout << "\nLenght = " << c.GetLenght(t) << std::endl;
		}

		else if (opt == 5 && existance_of_data)
		{
			std::cout  << "\nFull square = " << c.GetFullSquare() << std::endl;
		}

		else if (opt == 6 && existance_of_data)
		{
			std::cout << "\nSurface square = " << c.GetSurfaceSquare() << std::endl;
		}

		else if (opt == 7 && existance_of_data)
		{
			std::cout << "\nVolume = " << c.GetV() << std::endl;
		}

		else
			if (opt)
				std::cout << "\nTry again!" << std::endl;
	
		std::cout << std::endl;
	}
}