#include "gtest/gtest.h"

#include "../src/StaticPolygon/StaticPolygon.h"

#pragma comment (lib,"../../lib/StaticPolygon.lib")

struct PolygonTest : testing::Test
{
	Polygon c;
};

TEST_F(PolygonTest, DefaultConstructorTest)
{
	EXPECT_FLOAT_EQ(c.GetNumOfVertexes(), 0);
}

TEST_F(PolygonTest, CoordTest)
{
	Vertex v = { 0 , 1 };

	c += v;

	Vertex test_point = c[0];

	EXPECT_FLOAT_EQ(test_point.x, 0);

	EXPECT_FLOAT_EQ(test_point.y, 1);
}

TEST_F(PolygonTest, NumOfVertexesTest)
{
	for (int i = 0; i < 3; i++)
	{
		Vertex v = { i , i };

		c += v;
	}
	
	EXPECT_FLOAT_EQ(c.GetNumOfVertexes(), 3);
}

TEST_F(PolygonTest, NumOfCenterOfGravityTest)
{
	for (int i = 0; i < 3; i++)
	{
		Vertex v = { i, i };
		c += v;
	}
	
	EXPECT_FLOAT_EQ(c.CenterOfGravity(), 1.4142135);
}

TEST_F(PolygonTest, RotationTest)
{
	for (int i = 0; i < 2; i++)
	{
		Vertex v = { i, i };

		c += v;
	}

	c(90, 0);

	Vertex test_point = c[1];

	EXPECT_FLOAT_EQ(test_point.x, -1);
	
	EXPECT_FLOAT_EQ(test_point.y, -1);
}

TEST_F(PolygonTest, RotationExceptionAngleTest)
{
	for (int i = 0; i < 2; i++)
	{
		Vertex v = { i , i };
		
		c += v;
	}

	EXPECT_THROW(c(93, 0), std::invalid_argument);
}

TEST_F(PolygonTest, RotationExceptionPosTest)
{
	for (int i = 0; i < 2; i++)
	{
		Vertex v = { i , i };

		c += v;
	}

	EXPECT_THROW(c(90, 2), std::invalid_argument);
}

TEST_F(PolygonTest, MovingTest)
{
	for (int i = 0; i < 2; i++)
	{
		Vertex v = { i , i };

		c += v;
	}

	c(2.0, 2.0);

	Vertex test_point1 = c[0],
		test_point2 = c[1];

	EXPECT_FLOAT_EQ(test_point1.x, 2.0);

	EXPECT_FLOAT_EQ(test_point1.y, 2.0);
	
	EXPECT_FLOAT_EQ(test_point2.x, 3.0);
	
	EXPECT_FLOAT_EQ(test_point2.y, 3.0);
}
