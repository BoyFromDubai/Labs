#include "pch.h"
#include "../../Lab3/Polygon.h"

#pragma comment (lib,"../../lib/Polygon.lib")

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
	c.AddNewVertex(0, 1);

	Vertex test_point = c.GetValueOfVertex(0);

	EXPECT_FLOAT_EQ(test_point.x, 0);

	EXPECT_FLOAT_EQ(test_point.y, 1);
}

TEST_F(PolygonTest, NumOfVertexesTest)
{
	for (int i = 0; i < 3; i++)
		c.AddNewVertex(i, i);

	EXPECT_FLOAT_EQ(c.GetNumOfVertexes(), 3);
}

TEST_F(PolygonTest, NumOfCenterOfGravityTest)
{
	for (int i = 0; i < 3; i++)
		c.AddNewVertex(i, i);

	EXPECT_FLOAT_EQ(c.CenterOfGravity(), 1.4142135);
}

TEST_F(PolygonTest, RotationTest)
{
	for (int i = 0; i < 2; i++)
		c.AddNewVertex(i, i);

	c.Rotation(90, 0);

	Vertex test_point = c.GetValueOfVertex(1);

	EXPECT_FLOAT_EQ(test_point.x, -1);
	
	EXPECT_FLOAT_EQ(test_point.y, -1);
}

TEST_F(PolygonTest, RotationExceptionAngleTest)
{
	for (int i = 0; i < 2; i++)
		c.AddNewVertex(i, i);

	EXPECT_THROW(c.Rotation(93, 0), std::invalid_argument);
}

TEST_F(PolygonTest, RotationExceptionPosTest)
{
	for (int i = 0; i < 2; i++)
		c.AddNewVertex(i, i);

	EXPECT_THROW(c.Rotation(90, 2), std::invalid_argument);
}

TEST_F(PolygonTest, RotationExceptionTest)
{
	for (int i = 0; i < 2; i++)
		c.AddNewVertex(i, i);

	c.MovingPolygon(2, 2);

	Vertex test_point1 = c.GetValueOfVertex(0),
		test_point2 = c.GetValueOfVertex(1);

	EXPECT_FLOAT_EQ(test_point1.x, 2);

	EXPECT_FLOAT_EQ(test_point1.y, 2);
	
	EXPECT_FLOAT_EQ(test_point2.x, 3);
	
	EXPECT_FLOAT_EQ(test_point2.y, 3);
}
