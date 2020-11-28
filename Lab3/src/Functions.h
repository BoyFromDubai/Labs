#pragma once
#include <iostream>

template <typename T>
T GetNumber(const char* message, std::istream& in = std::cin, std::ostream& out = std::cout)
{
	T a{};

	while (1)
	{
		out << "\nEnter " << message << std::endl << "> ";

		if (in >> a)
			break;

		in.clear();

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		out << "Try again!\n";
	}

	return a;
}
