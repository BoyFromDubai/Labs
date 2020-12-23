#include <iostream>

#include "CLI.h"

int main()
{
	Data data;

	size_t opt = 1;

	while (1)
	{
		for (auto str : MSG)
			std::cout << str << std::endl;

		opt = GetNumber<size_t>("option");

		if (!opt)
			break;
		else if (--opt < std::size(CLI))
			CLI[opt](data);
		else
			std::cout << "Try another option!\n";

		std::cout << "\n" << data.cur_date << "\n\n";
	}

	DeleteDeps(data.map_dep);

	return 0;
}