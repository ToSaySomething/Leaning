#include "gtest/gtest.h"
#include "videocapture.h"
class videocapture_test : public testing::Test {
protected:
    
    virtual void SetUp()
    {
       std::cout<<" SetUp "<<std::endl;
    }


    virtual void TearDown()
    {
       std::cout<<" TearDown "<<std::endl;
    }
};

TEST(cwGetVideoCaptureVersion, case1)
{
    char* version = "xxxxx";
    int len = 5;
    EXPECT_EQ(0, cwGetVideoCaptureVersion(version,len)); 
}

