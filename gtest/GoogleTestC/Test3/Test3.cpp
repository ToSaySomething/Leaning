//Test3.cpp
//more data

#include "gtest/gtest.h"
#include "Sample.h"

Test(TestCaseName, TestName){
	EXPECT_EQ(1, FUN(1));
	EXPECT_EQ(2, FUN(2));
}


class MultiData : public ::test::Test
{
protected:
	void SetUp() override
	{
		a = 1;
		b = "string";
	}
	//void TearDown();
	int a;
	String b;
};
TEST_F(MultiData, TestName){
	EXPECT_EQ(a, FUN1(b));
	EXPECT_EQ(b, FUN2(a));
}

