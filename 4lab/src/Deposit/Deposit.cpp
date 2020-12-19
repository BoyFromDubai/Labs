#include "Deposit.h"

#include <iostream>

void Deposit::ChangeCurSum(double sum, Date date, char opt)
{
	if (opt == '-')
	{
		if (sum < 0 || sum > cur_sum)
			throw std::exception("[ERROR]");

		cur_sum -= sum;

		last_transaction_date = date;
	}

	else if (opt == '+')
	{
		cur_sum += sum;

		last_transaction_date = date;
	}

	else
		throw std::exception("Invalid option");
}

double Deposit::CalculateSumByDate(const Date date)
{
	if (last_transaction_date.year > date.year)
	{
		throw std::exception("[ERORR]");

		if (last_transaction_date.month > date.month)
		{
			throw std::exception("[ERORR]");

			if (last_transaction_date.day > date.day)
				throw std::exception("[ERORR]");
		}
	}


}

std::ostream& operator<<(std::ostream& ostr, const Date& date)
{
	return ostr << date.day << "/" << date.month << "/" << date.year;
}
