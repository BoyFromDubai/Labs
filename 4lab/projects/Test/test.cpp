#include "pch.h"

#include "../../src/Deposit/Deposit.h"

//#pragma comment (lib, "../../lib/Deposit.lib")

struct DepositsTest : testing::Test
{
	Deposit c;
};

TEST_F(DepositsTest, DefaultConstructorTest)
{
	EXPECT_FLOAT_EQ(c.GetSum(), 0);
	
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