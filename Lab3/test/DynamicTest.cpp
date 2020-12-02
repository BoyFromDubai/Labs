#include "gtest/gtest.h"

#include "../src//DynamicPolygon/DynamicPolygon.h"

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

	EXPECT_FLOAT_EQ(c[0].x, 0);
	EXPECT_FLOAT_EQ(c[0].y, 1);
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
		c += {i, i};

	EXPECT_FLOAT_EQ(c.CenterOfGravity(), 1.4142135);
}

TEST_F(PolygonTest, RotationTest)
{
	for (int i = 0; i < 2; i++)
		c += {i, i};

	c(90, 0);

	EXPECT_FLOAT_EQ(c[1].x, -1);

	EXPECT_FLOAT_EQ(c[1].y, -1);
}

TEST_F(PolygonTest, RotationExceptionPosTest)
{
	for (int i = 0; i < 2; i++)
		c += {i, i};

	EXPECT_THROW(c(90, 2), std::invalid_argument);
}

TEST_F(PolygonTest, PointTest)
{
	Polygon a({1,2});

	EXPECT_FLOAT_EQ(a[0].x, 1);
	EXPECT_FLOAT_EQ(a[0].y, 2);
}

TEST_F(PolygonTest, CoopTest)
{
	Vertex v[] = { {2,2}, {3,3} };

	c += v[0];
	c += v[1];

	Polygon a(c);

	EXPECT_FLOAT_EQ(a[0].x, 2);
	EXPECT_FLOAT_EQ(a[0].y, 2);

	EXPECT_FLOAT_EQ(a[1].x, 3);
	EXPECT_FLOAT_EQ(a[1].y, 3);
}

TEST_F(PolygonTest, EqTest)
{
	Vertex v[] = { {2, 2}, {3, 3} };

	Polygon a(2, v);

	c += {1, 1};

	c = a;

	EXPECT_FLOAT_EQ(c[0].x, 2);
	EXPECT_FLOAT_EQ(c[0].y, 2);

	EXPECT_FLOAT_EQ(c[1].x, 3);
	EXPECT_FLOAT_EQ(c[1].y, 3);
}

TEST_F(PolygonTest, MovingTest)
{
	for (int i = 0; i < 2; i++)
		c += {i, i};

	c(2.0, 2.0);

	EXPECT_FLOAT_EQ(c[0].x, 2.0);
	EXPECT_FLOAT_EQ(c[0].y, 2.0);

	EXPECT_FLOAT_EQ(c[1].x, 3.0);
	EXPECT_FLOAT_EQ(c[1].y, 3.0);
}
