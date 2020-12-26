#pragma once
#include <string>
#include <iosfwd>
/*
	@author BoyFromDubai
*/

struct Date
{
	int day,
		month,
		year;

	friend std::ostream& operator << (std::ostream&, const Date&);
};

class Deposit
{
private:

	Date acc_op_date, 
		last_transaction_date;
	double cur_sum,
		percentage_of_accural;

public:

	Deposit() :
		acc_op_date{},
		cur_sum{},
		percentage_of_accural{},
		last_transaction_date{}
	{};

	Deposit(Date op_date, double sum, double percentage) :
		acc_op_date{ op_date },
		last_transaction_date{ op_date },
		cur_sum { sum },
		percentage_of_accural{ percentage }
	{};

	virtual ~Deposit() = default;
	
	/*
		@brief Putting money on the account
	*/
	
	inline void AddMoney(int months) { cur_sum *= 1 + percentage_of_accural / 100 * months / 12; }
	/*
		@brief Changing las transaction date
	*/
	inline void ChangeLastTransDate(const Date date) { last_transaction_date = date; }

	/*
		@return Sum on the account
	*/

	inline double GetSum() const { return cur_sum; }

	double CalculateSumByDate(const Date);
	/*
	@brief Putting money on the acc or withdrawing it
	*/
	void ChangeCurSum(double, Date, char);
	/*
		@return Date of opening the account
	*/
	inline Date GetOpDate() const { return acc_op_date; }
	/*
		@return Last transaction date
	*/
	inline Date GetLastTransDate() const { return last_transaction_date; }
	/*
	* @return Percantage
	*/
	inline double GetPercentage() const { return percentage_of_accural; }
};

class CurrencyDeposit : public Deposit
{
private:

	std::string currency_name;

	double exchange_rate;

public:

	CurrencyDeposit() :
		currency_name{},
		exchange_rate{}
	{};

	CurrencyDeposit(Date op_date, double sum, double percent, double ex_rate, std::string curr_name) :
		Deposit(op_date, sum, percent),
		currency_name{ curr_name },
		exchange_rate{ ex_rate }
	{}; 
	/*
		@return Sum on currency acc in rubles
	*/


	inline double ConvertToRubles() const {	return GetSum() * exchange_rate; }
	/*
	@return Currency name
	*/
	inline std::string GetCurrName() const { return currency_name; }
	/*
	@return exchange rate
	*/
	inline double GetExchRate() const { return exchange_rate; }
};

class TermDeposit : public Deposit
{
private:

	Date acc_cl_date;

public:

	TermDeposit() :
		acc_cl_date{}
	{};

	TermDeposit(Date op_date, Date cl_date, double sum, double percent) :
		Deposit(op_date, sum, percent),
		acc_cl_date{ cl_date }
	{};
	/*
	@return Date of closing account
	*/
	inline  Date GetAccClDate() const { return acc_cl_date; }
};
