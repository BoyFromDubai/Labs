#pragma once
#include <iostream>
#include "Deposit/Deposit.h"
#include <map>
#include <vector>

template <typename T>
T GetNumber(const char* message, std::istream& in = std::cin, std::ostream& out = std::cout)
{
	T a{};

	while (1)
	{
		out << "\nEnter " << message << std::endl << "> ";

		if (in >> a )
			break;

		in.clear();

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		out << "Try again!\n";
	}

	return a;
}

Date ClDate(Date cur_date, int year, int month, int day)
{

	if (cur_date.year > year || month < 0 || day < 0)
		throw std::exception("Invalid data!");

	Date cl_date = {day, month, year};

	return cl_date;
}

Date ChangeTime(int months, Date cur_date)
{
	if (months < 0)
		throw std::exception("Invalid data!");

	int years = 0;

	if ((cur_date.month + months) / 12 && (cur_date.month + months) != 12)
	{
		years = (cur_date.month + months) / 12;

		cur_date.year += years;

		cur_date.month = (cur_date.month + months) % 12;
	}

	else
		cur_date.month += months;

	return cur_date;
}

void ExpiredDep(std::map<int, Deposit*>& map_dep, int months, Date cur_date)
{
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
				map_dep.erase(cur++);

				continue;
			}

			if (cl_date.year == cur_date.year && cl_date.month < cur_date.month)
			{
				map_dep.erase(cur++);

				continue;
			}

			if (cl_date.year == cur_date.year && cl_date.month == cur_date.month && cl_date.day < cur_date.day)
			{
				map_dep.erase(cur++);

				continue;
			}

			cur++;
		}

		else
			cur++;
	}
}

void ExpiredDep(std::map<int, Deposit*>& map_dep, std::vector<Deposit*>& vector, int months, Date cur_date)
{
	/*auto cur = map_dep.begin();
	auto end = map_dep.end();

	while (cur != end)
	{
		cur->second->AddMoney(months);

		if (auto cur_dep = dynamic_cast<const TermDeposit*>(cur->second))
		{
			Date cl_date = cur_dep->GetAccClDate();

			if (cl_date.year < cur_date.year)
			{
				map_dep.erase(cur++);

				continue;
			}

			if (cl_date.year == cur_date.year && cl_date.month < cur_date.month)
			{
				map_dep.erase(cur++);

				continue;
			}

			if (cl_date.year == cur_date.year && cl_date.month == cur_date.month && cl_date.day < cur_date.day)
			{
				map_dep.erase(cur++);

				continue;
			}

			cur++;
		}

		else
			cur++;
	}*/

	for (int i = 0; i < vector.size(); i++)
	{
		vector.pop_back();
	}
}

void DialogPrintDeps(const std::map<int, Deposit*> map_dep)
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

void DeleteDeps(std::map<int, Deposit*>& map_dep)
{
	auto cur = map_dep.begin(),
		end = map_dep.end();

	while (cur != end)
		map_dep.erase(cur++);
}

void PrintInfDep(std::map<int, Deposit*>::const_iterator it)
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