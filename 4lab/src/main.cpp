#include <iostream>

#include "Functions.h"
#include "Deposit\Deposit.h"

#include <map>

#pragma comment (lib, "../lib/Deposit.lib")

int main()
{
	Date cur_date = { 1, 1, 2001 };

	std::map<int, Deposit*> map_dep;
	
	std::string curr_name[] = { "Dollar", "Euro", "Franc" };

	int k = 10;

	int opt = 1;

	while (1)
	{
		std::cout << "1 - Change current date" << std::endl;
		std::cout << "2 - Add one more deposit" << std::endl;
		std::cout << "3 - Change sum" << std::endl;
		std::cout << "4 - Check info about deposit" << std::endl;
		std::cout << "5 - Show all deposits" << std::endl;
		std::cout << "6 - Close account" << std::endl;
		std::cout << "0 - Exit" << std::endl;

		opt = GetNumber<int>("option");

		if (!opt)
			break;

		else if (opt == 1)
		{
			int months = 0;

			months = GetNumber<int>("the number of months you want to add");
			
			try
			{
				cur_date = ChangeTime(months, cur_date);
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}

			ExpiredDep(map_dep, months, cur_date);
		}

		else if (opt == 2)
		{
			std::cout << "\n1 - Currency deposit\n2 - Term deposit\n3 - Ordinary deposit" << std::endl;

			int opt_dep = GetNumber<int>("option");

			double sum = -5;

			while (sum < 0)
				sum = GetNumber<double>("how much money to put on this account");

			if (opt_dep == 1)
			{
				int pos = 5;

				while (pos > 2 || pos < 0)
				{
					std::cout << "\t0 - Dollar\n\t1 - Euro\n\t2 - Franc" << std::endl;

					pos = GetNumber<int>("the number of currency");
				} 

				map_dep.emplace(k, new CurrencyDeposit(cur_date, sum, rand() % 10, (rand() + 132) % 100, curr_name[pos]));
			}
			
			if (opt_dep == 2)
			{
				int year = GetNumber<int>("a year of closing this acc"),
					month = GetNumber<int>("a month of closing this acc"),
					day = GetNumber<int>("a day of closing this acc");

				try
				{
					Date cl_date = ClDate(cur_date, year, month, day);

					map_dep.emplace(k, new TermDeposit(cur_date, cl_date, sum, rand() % 10));
				}

				catch (const std::exception& a)
				{
					std::cerr << "\n[ERORR]" << a.what() << std::endl;
				}

			}
			
			if (opt_dep == 3)
			{
				map_dep.emplace(k, new Deposit(cur_date, sum, rand() % 10));
			}

			k += 10;
		}

		else if (opt == 3)
		{
			char option = GetNumber<char>("+ ( to put money on account) \n - (to withdraw money)");

			double sum = -1;

			int pos = -1;

			while (pos < 0 || sum < 0)
			{
				sum = GetNumber<double>("sum");

				pos = GetNumber<int>("account number");
			}

			DialogPrintDeps(map_dep);

			auto it = map_dep.find(pos);

			if (it != map_dep.end())
			{
				try
				{
					it->second->ChangeCurSum(sum, cur_date, option);
				}

				catch (const std::exception& a)
				{
					std::cerr << "[ERORR]" << a.what() << std::endl;
				}
			}

			else
				std::cout << "\nDeposit was not found!" << std::endl;
		} 

		else if (opt == 4)
		{
			int pos = GetNumber<int>("account number");

			auto it = map_dep.find(pos);

			if (it != map_dep.end())
				PrintInfDep(it);

			else
				std::cout << "\nElement was not found" << std::endl;
		}

		else if (opt == 5)
		{
			DialogPrintDeps(map_dep);
		}

		else if (opt == 6)
		{
			int key = GetNumber<int>("account number");
			
			map_dep.erase(key);
		}

		else
			std::cout << "Try another option!\n";

		std::cout << "\n"<< cur_date << "\n\n";
	}

	DeleteDeps(map_dep);

	return 0;
}
