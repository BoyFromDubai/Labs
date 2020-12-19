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

	while (opt)
	{
		std::cout << "1 - Change current date" << std::endl;
		std::cout << "2 - Add one more deposit" << std::endl;
		std::cout << "3 - Change sum" << std::endl;
		std::cout << "4 - Check info about deposit" << std::endl;
		std::cout << "5 - Show all deposits" << std::endl;
		std::cout << "6 - Close account" << std::endl;
		std::cout << "0 - Exit" << std::endl;

		opt = GetNumber<int>("option");

		if (opt == 0)
			break;

		else if (opt == 1)
		{
			int months = 0,
				years = 0;

			months = GetNumber<int>("the number of months you want to add");
			
			try 
			{
				cur_date = ChangeTime(months, years, cur_date);
			}

			catch (const std::exception& a)
			{
				std::cerr << "\n[ERROR] " << a.what() << std::endl;
			}

			auto cur = map_dep.begin();
			auto end = map_dep.end();

			while (cur != end)
			{
				cur->second->AddMoney(months);

				if (auto cur_dep = dynamic_cast<const TermDeposit*>(cur->second))
				{
					Date cl_date = cur_dep->GetAccClDate();

					if (cl_date.year < cur_date.year)
					{
						std::cout << "\nTime is up and " << cur->first << " account was closed and money was paid off" << std::endl;

						map_dep.erase(cur++);

						continue;
					}

					if (cl_date.year == cur_date.year && cl_date.month < cur_date.month)
					{
						std::cout << "\nTime is up and " << cur->first << " account was closed and money was paid off" << std::endl;

						map_dep.erase(cur++);

						continue;
					}

					if (cl_date.year == cur_date.year && cl_date.month == cur_date.month && cl_date.day < cur_date.day)
					{
						std::cout << "\nTime is up and " << cur->first << " account was closed and money was paid off" << std::endl;

						map_dep.erase(cur++);

						continue;
					}

					cur++;
				}

				else
					cur++;
			}

		}

		else if (opt == 2)
		{
			std::cout << "\n1 - Currency deposit\n2 - Term deposit\n3 - Ordinary deposit" << std::endl;

			int opt_dep = GetNumber<int>("option");

			double sum = -5;

			while (sum < 0)
				sum = GetNumber<double>("how much money to put on your account");

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
				try
				{
					int year = GetNumber<int>("a year of closing this acc"),
						 month = GetNumber<int>("a month of closing this acc"),
						 day = GetNumber<int>("a day of closing this acc");

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
			double sum = -1;

			char option = GetNumber<char>("+ ( to put money on account) \n - (to withdraw money)");

			int pos = -1;

			for (const auto& [key, value] : map_dep)
			{
				if (!value)
					continue;

				if (auto cur_dep = dynamic_cast<const CurrencyDeposit*>(value))
					std::cout << "\nCurrency Deposit\n";

				else if (auto cur_dep = dynamic_cast<const TermDeposit*>(value))
					std::cout << "\nTerm deposit\n";

				else if (auto cur_dep = dynamic_cast<const Deposit*>(value))
					std::cout << "\nOrdinary Deposit\n";

				std::cout << key << " - NUMBER OF DEPOSIT\n" << value->GetSum() << " - Current sum\n";
			}
			
			while (pos < 0 || sum < 0)
			{
				sum = GetNumber<double>("sum");

				pos = GetNumber<int>("account number");
			}

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
				std::cout << "Deposit was not found!" << std::endl;
		} 

		else if (opt == 4)
		{
			int pos = GetNumber<int>("account number");

			auto it = map_dep.find(pos);


			if (it != map_dep.end())
			{
				std::cout << "\n" << it->first << " - NUMBER OF DEPOSIT\n" << it->second->GetSum() << " - Current sum\n";
				std::cout << it->second->GetOpDate() << " - Date of opening the deposit\n";
				std::cout << it->second->GetLastTransDate() << " - Date of last transaction\n";
				std::cout << it->second->GetPercentage() << "% - Percentage\n";

				if (auto cur_dep = dynamic_cast<const CurrencyDeposit*>(it->second))
				{
					std::cout << cur_dep->GetCurrName() << " - Currency name" << "\n";
					std::cout << cur_dep->ConvertToRubles() << " - Sum in rubles" << "\n";
					std::cout << cur_dep->GetExchRate() << " rubles - Exchange rate" << "\n";
				}

				if (auto cur_dep = dynamic_cast<const TermDeposit*>(it->second))
				{
					std::cout << cur_dep->GetAccClDate() << " - Date of closing account" << "\n";
				}
			}
			/*auto cur = map_dep.begin();
			auto end = map_dep.end();

			for (const auto& [key, value] : map_dep)
			{
				if (key == pos)
				{
					if (!value)
						continue;

					std::cout << "\n" << key << " - NUMBER OF DEPOSIT\n" << value->GetSum() << " - Current sum\n";
					std::cout << value->GetOpDate() << " - Date of opening the deposit\n";
					std::cout << value->GetLastTransDate() << " - Date of last transaction\n";
					std::cout << value->GetPercentage() << "% - Percentage\n";

					if (auto cur_dep = dynamic_cast<const CurrencyDeposit*>(value))
					{
						std::cout << cur_dep->GetCurrName() << " - Currency name" << "\n";
						std::cout << cur_dep->ConvertToRubles() << " - Sum in rubles" << "\n";
						std::cout << cur_dep->GetExchRate() << " rubles - Exchange rate" << "\n";
					}

					if (auto cur_dep = dynamic_cast<const TermDeposit*>(value))
					{
						std::cout << cur_dep->GetAccClDate() << " - Date of closing account" << "\n";
					}
				}
			}*/
		}

		else if (opt == 5)
		{
			for (const auto& [key, value] : map_dep)
			{
				if (!value)
					continue;

				std::cout << "\n" << key << " - NUMBER OF DEPOSIT\n" << value->GetSum() << " - Current sum\n";
				std::cout << value->GetOpDate() << " - Date of opening the deposit\n";
				std::cout << value->GetLastTransDate() << " - Date of last transaction\n";
				std::cout << value->GetPercentage() << "% - Percentage\n";

				if (auto cur_dep = dynamic_cast<const CurrencyDeposit*>(value))
				{
					std::cout << cur_dep->GetCurrName() << " - Currency name" << "\n";
					std::cout << cur_dep->ConvertToRubles() << " - Sum in rubles" << "\n";
					std::cout << cur_dep->GetExchRate() << " rubles - Exchange rate" << "\n";
				}

				if (auto cur_dep = dynamic_cast<const TermDeposit*>(value))
				{
					std::cout << cur_dep->GetAccClDate() << " - Date of closing account" << "\n";
				}
			}
		}

		else if (opt == 6)
		{
			int pos = GetNumber<int>("account number");

			auto cur = map_dep.begin();
			auto end = map_dep.end();

			while (cur != end)
			{
				if (cur->first == pos)
				{
					map_dep.erase(cur);

					std::cout << "\nAccount was found and closed" << std::endl;

					break;
				}

				else
					cur++;
			}
		}

		else
			std::cout << "Try another option!\n";

		std::cout << "\n"<< cur_date << "\n\n";
	}

	auto cur = map_dep.begin(),
		end = map_dep.end();

	while (cur != end)
		map_dep.erase(cur++);

	return 0;
}
