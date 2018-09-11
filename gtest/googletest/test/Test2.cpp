//Test2.cpp
//some data

#include "gtest/gtest.h"
#include "Sample.h"

TEST(fun, testcase2)
{
	EXPECT_EQ(1, fun(101,5));
	EXPECT_EQ(2, fun(10,4));
}
