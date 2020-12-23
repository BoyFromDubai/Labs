#pragma once
#include <string>
#include <iosfwd>

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
	
protected:
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

	inline void AddMoney(int months) { cur_sum *= 1 + percentage_of_accural / 100 * months / 12; }

	inline void ChangeLastTransDate(const Date date) { last_transaction_date = date; }

	inline double GetSum() const { return cur_sum; }

	double CalculateSumByDate(const Date);

	void ChangeCurSum(double, Date, char);

	inline Date GetOpDate() const { return acc_op_date; }
	
	inline Date GetLastTransDate() const { return last_transaction_date; }

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

	inline double ConvertToRubles() const { return cur_sum * exchange_rate; }

	inline std::string GetCurrName() const { return currency_name; }

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

	inline Date GetAccClDate() const { return acc_cl_date; }
};
