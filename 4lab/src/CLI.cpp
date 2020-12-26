#include "CLI.h"
#include "Functions.h"

#include <fstream>
#include <iostream>

#pragma comment (lib, "../lib/Deposit.lib")

const std::string DepositCLI::MSGS[]
{
	"1 - Change current date",
	"2 - Add one more deposit",
	"3 - Add currency",
	"4 - Check info about deposit",
	"5 - Show all deposits",
	"6 - Close account",
	"7 - Change sum",
	"8 - Load to file",
	"9 - Load from file",
	"0 - Exit"
};

void(DepositCLI::* const DepositCLI::CLI[])()
{
	&DepositCLI::ChangeCurrentDate,
	&DepositCLI::AddDeposit,
	&DepositCLI::AddCurrency,
	&DepositCLI::CheckInfo,
	&DepositCLI::ShowAllDeposits,
	&DepositCLI::CloseAccount,
	&DepositCLI::ChangeSum,
	&DepositCLI::FLoad,
	&DepositCLI::FWrite
};

DepositCLI::~DepositCLI()
{
	DeleteDeps(map_dep);
}

void DepositCLI::ChangeCurrentDate()
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

void DepositCLI::AddCurrency()
{
	currency.push_back(GetNumber<std::string>("currency name"));

	curr_rate.push_back((rand() + 132) % 100);
}

void DepositCLI::CheckInfo()
{
	int pos = GetNumber<int>("account number");

	auto it = map_dep.find(pos);

	if (it != map_dep.end())
		PrintInfDep(it);

	else
		std::cout << "\nElement was not found\n";
}

void DepositCLI::ShowAllDeposits()
{
	DialogPrintDeps(map_dep);
}

void DepositCLI::CloseAccount()
{
	int key = GetNumber<int>("account number");

	std::map<int, Deposit*>::iterator it = map_dep.find(key);

	if (it != map_dep.end())
	{
		delete it->second;

		map_dep.erase(it);
	}

	else
	{
		std::cout << "\nAccount was not found\n";
	}
}

void DepositCLI::ChangeSum()
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

void DepositCLI::AddDeposit()
{
	if (currency.size())
	{
		std::cout << "\n1 - Currency deposit";
	}

	std::cout << "\n2 - Term deposit\n3 - Ordinary deposit\n";

	int opt_dep = GetNumber<int>("option");

	double sum = -5;

	while (sum < 0)
		sum = GetNumber<double>("how much money to put on this account");

	if (opt_dep == 1 && currency.size())
	{
		int pos = -1;

		while (pos < 0 || pos >= currency.size())
		{
			for (int i = 0; i < currency.size(); i++)
			{
				std::cout << "\t" << i << " - " << currency[i] << " " << curr_rate[i] << " rubles" << std::endl;
			}

			pos = GetNumber<int>("the number of currency");
		}

		AddDep<CurrencyDeposit>(cur_date, sum, rand() % 10, curr_rate[pos], currency[pos]);
	}

	else if (opt_dep == 2)
	{
		int year = GetNumber<int>("a year of closing this acc"),
			month = GetNumber<int>("a month of closing this acc"),
			day = GetNumber<int>("a day of closing this acc");

		try
		{
			Date cl_date = ClDate(cur_date, year, month, day);

			AddDep<TermDeposit>(cur_date, cl_date, sum, rand() % 10);
		}

		catch (const std::exception& a)
		{
			std::cerr << "\n[ERORR]" << a.what() << std::endl;
		}
	}

	else if (opt_dep == 3)
	{
		AddDep<Deposit>(cur_date, sum, rand() % 10);
	}
}

void DepositCLI::FLoad()
{
	std::ofstream fout;

	std::string f_name = GetNumber<std::string>("file name");

	fout.open(f_name);

	if (!fout.is_open())
		throw std::exception("[ERROR]");

	fout << cur_date << "\n";

	fout << currency.size() << "\n";

	for (int i = 0; i < currency.size(); i++)
	{
		fout << currency[i] << " ";

		fout << curr_rate[i] << "\n";
	}

	for (auto it = map_dep.begin(); it != map_dep.end(); it++)
	{
		if (auto cur_dep = dynamic_cast<CurrencyDeposit*>(it->second))
		{
			fout << "Currency" << "\n";
		}


		else if (auto cur_dep = dynamic_cast<TermDeposit*>(it->second))
		{
			fout << "Term" << "\n";
		}

		else if (auto cur_dep = dynamic_cast<Deposit*>(it->second))
		{
			fout << "Ordinary" << "\n";
		}

		fout << it->second->GetSum() << "\n";
		fout << it->second->GetOpDate() << "\n";
		fout << it->second->GetLastTransDate() << "\n";
		fout << it->second->GetPercentage() << "\n";

		if (auto cur_dep = dynamic_cast<CurrencyDeposit*>(it->second))
		{
			fout << cur_dep->GetCurrName() << "\n";
		}

		if (auto cur_dep = dynamic_cast<TermDeposit*>(it->second))
		{
			fout << cur_dep->GetAccClDate() << "\n";
		}
	}

	fout.close();
}

void DepositCLI::FWrite()
{
	DeleteDeps(map_dep);

	int size = 0;

	std::ifstream fin;

	std::string f_name = GetNumber<std::string>("file name");

	fin.open(f_name);

	if (!fin.is_open())
		throw std::exception("[ERROR]");

	int cur_day, cur_month, cur_year;

	fin >> cur_day;
	fin.ignore(1);
	fin >> cur_month;
	fin.ignore(1);
	fin >> cur_year;

	cur_date = { cur_day, cur_month, cur_year };

	fin >> size;

	for (int i = 0; i < size; i++)
	{
		std::string cur_name;

		fin >> cur_name;

		currency.push_back(cur_name);

		int cr = 0;

		fin >> cr;

		curr_rate.push_back(cr);
	}

	while (!fin.eof())
	{
		double sum = 0;

		std::string dep_name;

		int day, month, year, last_trans_day, last_trans_month, last_trans_year, percentage;

		fin >> dep_name;
		fin >> sum;

		fin >> day;
		fin.ignore(1);
		fin >> month;
		fin.ignore(1);
		fin >> year;

		fin >> last_trans_day;
		fin.ignore(1);
		fin >> last_trans_month;
		fin.ignore(1);
		fin >> last_trans_year;

		fin >> percentage;

		if (dep_name == "Currency")
		{
			std::string curr_name;

			fin >> curr_name;

			int pos = 0;

			for (int i = 0; i < currency.size(); i++)
			{
				if (currency[i] == curr_name)
					pos = i;
			}

			AddDep<CurrencyDeposit>(cur_date, sum, percentage, curr_rate[pos], currency[pos]);
		}

		else if (dep_name == "Term")
		{
			int cl_day, cl_month, cl_year;

			fin >> cl_day;
			fin.ignore(1);
			fin >> cl_month;
			fin.ignore(1);
			fin >> cl_year;

			AddDep<TermDeposit>(cur_date, Date{ cl_day, cl_month, cl_year }, sum, percentage);
		}

		else if (dep_name == "Ordinary")
			AddDep<Deposit>(cur_date, sum, percentage);

	}

	fin.close();
}