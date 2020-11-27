#pragma once
#include <iostream>

template <typename T>
T GetNumber(const char* message, std::istream& in)
{
	T a{};

	while (1)
	{
		std::cout << "\nEnter " << message << std::endl << "> ";

		if (in >> a)
			break;

		in.clear();

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Try again!\n";
	}

	return a;
}
