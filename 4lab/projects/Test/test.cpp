#include "pch.h"

#include "../../src/Deposit/Deposit.h"
#include"../../src/CLI.h"
#include"../../src/Functions.h"

#include"../../src/MyVector.h"

#pragma comment (lib, "../../lib/Deposit.lib")

struct DepositsTest : testing::Test
{
	DepositCLI cli;

};

struct VectorTest : testing::Test
{
	MyVector<int> vect;
};

TEST_F(DepositsTest, DepositAdd)
{
	cli.AddDep<Deposit>(Date{ 1, 1, 2001 }, 10000, 5);
	
	auto map = cli.GetMap();
	auto it = map.begin();

	EXPECT_FLOAT_EQ(it->second->GetSum(), 10000);
	EXPECT_FLOAT_EQ(it->second->GetOpDate().day, 1);
	EXPECT_FLOAT_EQ(it->second->GetOpDate().month, 1);
	EXPECT_FLOAT_EQ(it->second->GetOpDate().year, 2001);

	EXPECT_FLOAT_EQ(it->second->GetLastTransDate().day, 1);
	EXPECT_FLOAT_EQ(it->second->GetLastTransDate().month, 1);
	EXPECT_FLOAT_EQ(it->second->GetLastTransDate().year, 2001);

	EXPECT_FLOAT_EQ(it->second->GetPercentage(), 5);
}

TEST_F(DepositsTest, CurrencyDepositAdd)
{
	cli.AddDep<CurrencyDeposit>(Date{ 1, 1, 2001 }, 10000, 5, 74, "Dollar");
	
	auto map = cli.GetMap();
	auto it = map.begin();

	auto dep = dynamic_cast<CurrencyDeposit*>(it->second);

	EXPECT_FLOAT_EQ(dep->GetSum(), 10000);
	EXPECT_FLOAT_EQ(dep->GetOpDate().day, 1);
	EXPECT_FLOAT_EQ(dep->GetOpDate().month, 1);
	EXPECT_FLOAT_EQ(dep->GetOpDate().year, 2001);

	EXPECT_FLOAT_EQ(dep->GetLastTransDate().day, 1);
	EXPECT_FLOAT_EQ(dep->GetLastTransDate().month, 1);
	EXPECT_FLOAT_EQ(dep->GetLastTransDate().year, 2001);

	EXPECT_FLOAT_EQ(dep->GetPercentage(), 5);

	EXPECT_FLOAT_EQ(dep->GetExchRate(), 74);
	EXPECT_EQ(dep->GetCurrName(), "Dollar");
}

TEST_F(DepositsTest, TermDepositAdd)
{
	cli.AddDep<TermDeposit>(Date{ 1, 1, 2001 }, Date{ 1, 1, 2002 }, 10000, 5);

	auto map = cli.GetMap();
	auto it = map.begin();

	auto dep = dynamic_cast<TermDeposit*>(it->second);

	EXPECT_FLOAT_EQ(dep->GetSum(), 10000);

	EXPECT_FLOAT_EQ(dep->GetOpDate().day, 1);
	EXPECT_FLOAT_EQ(dep->GetOpDate().month, 1);
	EXPECT_FLOAT_EQ(dep->GetOpDate().year, 2001);

	EXPECT_FLOAT_EQ(dep->GetLastTransDate().day, 1);
	EXPECT_FLOAT_EQ(dep->GetLastTransDate().month, 1);
	EXPECT_FLOAT_EQ(dep->GetLastTransDate().year, 2001);

	EXPECT_FLOAT_EQ(dep->GetAccClDate().day, 1);
	EXPECT_FLOAT_EQ(dep->GetAccClDate().month, 1);
	EXPECT_FLOAT_EQ(dep->GetAccClDate().year, 2002);

	EXPECT_FLOAT_EQ(dep->GetPercentage(), 5);
}

TEST_F(VectorTest, AddElems)
{
	for (int i = 0; i < 5; i++)
		vect.push_back(i);

	EXPECT_FLOAT_EQ(vect[0], 0);
	EXPECT_FLOAT_EQ(vect[1], 1);
	EXPECT_FLOAT_EQ(vect[2], 2);
	EXPECT_FLOAT_EQ(vect[3], 3);
	EXPECT_FLOAT_EQ(vect[4], 4);
}

TEST_F(VectorTest, Exception)
{
	EXPECT_ANY_THROW(vect[-1]);
	EXPECT_ANY_THROW(MyVector<int> a(-5));
}

TEST_F(DepositsTest, ChangeCurDate)
{
	EXPECT_ANY_THROW(ChangeTime(-1, Date{ 1, 1, 2001 }));
}
