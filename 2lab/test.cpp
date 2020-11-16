#include "pch.h"
#include <iostream>

#include "../2labLib/Cycloid.h"

struct CycloidTest : testing::Test
{
	Cycloid c;
};

TEST_F(CycloidTest, DefaultConstructorTest) 
{
	EXPECT_FLOAT_EQ(c.GetR(), 0);
}

TEST_F(CycloidTest, NegativeRadius)
{
	EXPECT_THROW(c.SetR(-2), std::invalid_argument);
}

TEST_F(CycloidTest, FullSquare)
{
	c.SetR(5);

	EXPECT_FLOAT_EQ(c.GetFullSquare(), 235.6194);
}

TEST_F(CycloidTest, GetRadiusOfCurvature)
{
	c.SetR(2);

	EXPECT_FLOAT_EQ(c.GetRadiusOfCurvature(60), 4);
}

TEST_F(CycloidTest, GetLenght)
{
	c.SetR(4);

	EXPECT_FLOAT_EQ(c.GetLenght(90), 7.594848);
}

TEST_F(CycloidTest, GetSurfaceSquare)
{ 
	c.SetR(10);

	EXPECT_FLOAT_EQ(c.GetSurfaceSquare(), 6597.344);
}

TEST_F(CycloidTest, GetVolume)
{
	c.SetR(1);

	EXPECT_FLOAT_EQ(c.GetV(), 15.707963);
}

TEST_F(CycloidTest, GetCoords)
{
	c.SetR(15);

	Point b = c.GetCoords(15);

	EXPECT_FLOAT_EQ(b.x, 0.044705141);

	EXPECT_FLOAT_EQ(b.y, 0.51111263);
}