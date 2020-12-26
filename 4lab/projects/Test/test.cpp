#include "pch.h"

#include "../../src/Deposit/Deposit.h"
#include"../../src/CLI.h"

//#pragma comment (lib, "../../lib/Deposit.lib")

struct DepositsTest : testing::Test
{
	DepositCLI cli;

};

TEST_F(DepositsTest, DefaultConstructorTest)
{
	cli.AddDep(Date { 1, 1, 2001 }, 1, 1);

	EXPECT_FLOAT_EQ(cli.CLI[3], 0);
	
	EXPECT_FLOAT_EQ(c.GetLastTransDate().day, 0);
	EXPECT_FLOAT_EQ(c.GetLastTransDate().month, 0);
	EXPECT_FLOAT_EQ(c.GetLastTransDate().year, 0);
	
	EXPECT_FLOAT_EQ(c.GetOpDate().day, 0);
	EXPECT_FLOAT_EQ(c.GetOpDate().month, 0);
	EXPECT_FLOAT_EQ(c.GetOpDate().year, 0);

	EXPECT_FLOAT_EQ(c.GetPercentage(), 0);

	 
}

TEST_F(DepositsTest, Defau)
{

}