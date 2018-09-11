//Test4.cpp
//Test error

#include "gtest/gtest.h"
#include "Sample.h"

Test(FunctionName, ERRORTestCase){
	EXPECT_THROW(FUN(1), exception_type)
	EXPECT_ANY_THROW(FUN(1))
	EXPECT_NO_THROW(FUN(1))
}


