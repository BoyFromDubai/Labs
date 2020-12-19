#pragma once
#include <iostream>
#include "Deposit/Deposit.h"
#include <map>


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

Date ChangeTime(int months, int years, Date cur_date)
{
	if (months < 0)
		throw std::exception("Invalid data!");

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

