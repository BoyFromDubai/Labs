#include <iostream>

#include "CLI.h"
#include "Functions.h"

int main()
{
	DepositCLI cli;

	size_t opt = 1;

	while (1)
	{
		for (auto str : DepositCLI::MSGS)
			std::cout << str << std::endl;

		opt = GetNumber<size_t>("option");

		if (!opt)
			break;

		else if (--opt < DepositCLI::OPTS_NUM)
			(cli.*DepositCLI::CLI[opt])();
		
		else
			std::cout << "Try another option!\n";

		std::cout << "\n" << cli.GetCurDate() << "\n\n";
	}

	return 0;
}