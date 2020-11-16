#pragma once
#include <iostream>

template <typename T>
T GetNumber(const char* message)
{
	std::cout << "\nEnter " << message << std::endl << "> ";

	T a{};

	while (1)
	{
		if (std::cin >> a)
			break;

		std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Try again!\n";
	}

	return a;
}
