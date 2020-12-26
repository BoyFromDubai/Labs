#pragma once

#include <string>
#include <map>
#include <vector>

#include "Deposit\Deposit.h"
#include "MyVector.h"

class DepositCLI
{
public:
	static const size_t OPTS_NUM = 10;

	static const std::string MSGS[OPTS_NUM];
	static void(DepositCLI::* const CLI[OPTS_NUM])();

public:
	~DepositCLI()
	{
		auto cur = map_dep.begin(),
			end = map_dep.end();

		while (cur != end)
		{
			delete cur->second;

			map_dep.erase(cur++);
		}
	};

	void ChangeCurrentDate();
	void AddDeposit();
	void AddCurrency();
	void CheckInfo();
	void ShowAllDeposits();
	void CloseAccount();
	void ChangeSum();
	void FLoad();
	void FWrite();

	Date GetCurDate() const { return cur_date; }

	template<typename _Dep, typename... _Args>
	void AddDep(_Args... args)
	{
		int k{};

		for (auto& [id, _] : map_dep)
			k = std::max(k, id);
		  
		k++;

		map_dep.emplace(map_dep.size() + 1, new _Dep(args...));
	}

	std::map<int, Deposit*> GetMap() { return map_dep; }

private:
	Date cur_date = { 1, 1, 2001 };

	std::map<int, Deposit*> map_dep;

	MyVector<std::string> currency;
	MyVector<int> curr_rate;
};
