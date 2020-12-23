#pragma once
#include <string>
#include <fstream>

#include "Functions.h"
#include "Deposit\Deposit.h"

#pragma comment (lib, "../lib/Deposit.lib")

struct Data
{
	Date cur_date = { 1, 1, 2001 };

	std::map<int, Deposit*> map_dep;

	std::vector<std::string> currency;
	std::vector<int> curr_rate;
};

void ChangeCurrentDateCLI(Data& data);
void AddDepositCLI(Data& data);
void AddCurrencyCLI(Data& data);
void CheckInfoCLI(Data& data);
void ShowAllDepositsCLI(Data& data);
void CloseAccountCLI(Data& data);
void ChangeSumCLI(Data& data);
void FLoadCLI(Data& deps_info);
void FWriteCLI(Data& deps_info);

void DeleteCurrency(Data&);

void AddDep(Data& data, int opt_dep, double sum, int curr_name, Date cl_date);

void (*CLI[])(Data&)
{
	ChangeCurrentDateCLI,
		AddDepositCLI,
		AddCurrencyCLI,
		CheckInfoCLI,
		ShowAllDepositsCLI,
		CloseAccountCLI,
		ChangeSumCLI,
		FLoadCLI,
		FWriteCLI
};

std::string MSG[]
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

void FLoadCLI(Data& deps_info)
{
	std::ofstream fout;

	std::string f_name = GetNumber<std::string>("file name");

	fout.open(f_name);

	if (!fout.is_open())
		throw std::exception("[ERROR]");

	fout << deps_info.cur_date << "\n";

	fout << deps_info.currency.size() << "\n";

	for (int i = 0; i < deps_info.currency.size(); i++)
	{
		fout << deps_info.currency[i] << " ";

		fout << deps_info.curr_rate[i] << "\n";
	}

	for (auto it = deps_info.map_dep.begin(); it != deps_info.map_dep.end(); it++)
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

void FWriteCLI(Data& deps_info)
{
	DeleteDeps(deps_info.map_dep);
	DeleteCurrency(deps_info);

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

	deps_info.cur_date = { cur_day, cur_month, cur_year };

	fin >> size;

	for (int i = 0; i < size; i++)
	{
		std::string cur_name;

		fin >> cur_name;

		deps_info.currency.push_back(cur_name);

		int curr_rate = 0;

		fin >> curr_rate;

		deps_info.curr_rate.push_back(curr_rate);
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

			for (int i = 0; i < deps_info.currency.size(); i++)
			{
				if (deps_info.currency[i] == curr_name)
					pos = i;
			}

			AddDep(deps_info, 1, sum, pos, {});
		}

		else if (dep_name == "Term")
		{
			int cl_day, cl_month, cl_year;

			fin >> cl_day;
			fin.ignore(1);
			fin >> cl_month;
			fin.ignore(1);
			fin >> cl_year;

			AddDep(deps_info, 2, sum, {}, { cl_day, cl_month, cl_year });
		}

		else if (dep_name == "Ordinary")
			AddDep(deps_info, 3, sum, {}, {});

	}

	fin.close();
}

void ChangeCurrentDateCLI(Data& data)
{
	int months = 0;

	months = GetNumber<int>("the number of months you want to add");

	try
	{
		data.cur_date = ChangeTime(months, data.cur_date);
	}

	catch (const std::exception& a)
	{
		std::cerr << "\n[ERROR] " << a.what() << std::endl;
	}

	ExpiredDep(data.map_dep, months, data.cur_date);
}

/*void AddDepositCLI(Data& data)
{
	if (data.currency.size())
	{
		std::cout << "\n1 - Currency deposit";
	}

	std::cout << "\n2 - Term deposit\n3 - Ordinary deposit\n";

	int opt_dep = GetNumber<int>("option");

	double sum = -5;

	while (data.currency.size() && sum < 0)
		sum = GetNumber<double>("how much money to put on this account");

	int k{};

	// for (auto it = std::begin(map_dep); it != std::end(map_dep); ++it)
	for (auto& [id, _] : data.map_dep)
		k = std::max(k, id);

	k++;

	if (opt_dep == 1 && data.currency.size())
	{
		int pos = -1;

		while (pos < 0 || pos >= data.currency.size())
		{
			for (int i = 0; i < data.currency.size(); i++)
			{
				std::cout << "\t" << i << " - " << data.currency[i] << " " << data.curr_rate[i] << " rubles" << std::endl;
			}

			pos = GetNumber<int>("the number of currency");
		}

		data.map_dep.emplace(k, new CurrencyDeposit(data.cur_date, sum, rand() % 10, data.curr_rate[pos], data.currency[pos]));
	}

	if (opt_dep == 2)
	{
		int year = GetNumber<int>("a year of closing this acc"),
			month = GetNumber<int>("a month of closing this acc"),
			day = GetNumber<int>("a day of closing this acc");

		try
		{
			Date cl_date = ClDate(data.cur_date, year, month, day);

			data.map_dep.emplace(data.map_dep.size() + 1, new TermDeposit(data.cur_date, cl_date, sum, rand() % 10));
		}

		catch (const std::exception& a)
		{
			std::cerr << "\n[ERORR]" << a.what() << std::endl;
		}

	}

	if (opt_dep == 3)
	{
		data.map_dep.emplace(k, new Deposit(data.cur_date, sum, rand() % 10));
	}
}

void AddDep(Data& data, int kind_of_dep, int sum, int curr_name = 0, Date cl_date = {})
{

}*/

void AddCurrencyCLI(Data& data)
{
	data.currency.push_back(GetNumber<std::string>("currency name"));
	
	data.curr_rate.push_back((rand() + 132) % 100);
}

void CheckInfoCLI(Data& data)
{
	int pos = GetNumber<int>("account number");

	auto it = data.map_dep.find(pos);

	if (it != data.map_dep.end())
		PrintInfDep(it);

	else
		std::cout << "\nElement was not found\n";
}

void ShowAllDepositsCLI(Data& data)
{
	DialogPrintDeps(data.map_dep);
}

void CloseAccountCLI(Data& data)
{
	int key = GetNumber<int>("account number");

	std::map<int, Deposit*>::iterator it = data.map_dep.find(key);

	if (it != data.map_dep.end())
	{
		delete it->second;

		data.map_dep.erase(it);
	}

	else
	{
		std::cout << "\nAccount was not found\n";
	}
}

void ChangeSumCLI(Data& data)
{
	char option = GetNumber<char>("+ ( to put money on account) \n - (to withdraw money)");

	double sum = -1;

	int pos = -1;

	while (pos < 0 || sum < 0)
	{
		sum = GetNumber<double>("sum");

		pos = GetNumber<int>("account number");
	}

	DialogPrintDeps(data.map_dep);

	auto it = data.map_dep.find(pos);

	if (it != data.map_dep.end())
	{
		try
		{
			it->second->ChangeCurSum(sum, data.cur_date, option);
		}

		catch (const std::exception& a)
		{
			std::cerr << "[ERORR]" << a.what() << std::endl;
		}
	}

	else
		std::cout << "\nDeposit was not found!" << std::endl;
}

void AddDepositCLI(Data& data)
{
	if (data.currency.size())
	{
		std::cout << "\n1 - Currency deposit";
	}

	std::cout << "\n2 - Term deposit\n3 - Ordinary deposit\n";

	int opt_dep = GetNumber<int>("option");

	double sum = -5;

	while (sum < 0)
		sum = GetNumber<double>("how much money to put on this account");
	
	if (opt_dep == 1 && data.currency.size())
	{
		int pos = -1;

		while (pos < 0 || pos >= data.currency.size())
		{
			for (int i = 0; i < data.currency.size(); i++)
			{
				std::cout << "\t" << i << " - " << data.currency[i] << " " << data.curr_rate[i] << " rubles" << std::endl;
			}

			pos = GetNumber<int>("the number of currency");
		}

		AddDep(data, opt_dep, sum, pos, data.cur_date);
	}

	else if (opt_dep == 2)
	{
		int year = GetNumber<int>("a year of closing this acc"),
			month = GetNumber<int>("a month of closing this acc"),
			day = GetNumber<int>("a day of closing this acc");

		try
		{
			Date cl_date = ClDate(data.cur_date, year, month, day);

			AddDep(data, opt_dep, sum, 0, cl_date);
		}

		catch (const std::exception& a)
		{
			std::cerr << "\n[ERORR]" << a.what() << std::endl;
		}
	}

	else if (opt_dep == 3)
	{
		AddDep(data, opt_dep, sum, 1, data.cur_date);
	}
}

void AddDep(Data& data, int opt_dep, double sum, int curr_name, Date cl_date)
{
	int k{};

	// for (auto it = std::begin(map_dep); it != std::end(map_dep); ++it)
	for (auto& [id, _] : data.map_dep)
		k = std::max(k, id);

	k++;

	if (opt_dep == 1)
	{
		data.map_dep.emplace(k, new CurrencyDeposit(data.cur_date, sum, rand() % 10, data.curr_rate[curr_name], data.currency[curr_name]));
	}

	if (opt_dep == 2)
	{
		data.map_dep.emplace(data.map_dep.size() + 1, new TermDeposit(data.cur_date, cl_date, sum, rand() % 10));
	}

	if (opt_dep == 3)
	{
		data.map_dep.emplace(k, new Deposit(data.cur_date, sum, rand() % 10));
	}
}

void DeleteCurrency(Data& data)
{
	for (int i = 0; i < data.currency.size(); i++)
	{
		data.currency.pop_back();
		data.curr_rate.pop_back();
	}
}