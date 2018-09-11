#include "cbox.h"
#include "gtest/gtest.h"


class CBox_test : public testing::Test {
protected:
    CBox* c;
    virtual void SetUp()
    {
        c = new CBox(2, 3, 4);
    }


    virtual void TearDown()
    {
        delete this->c;
    }
};

TEST(CBox, case1)
{
    CBox box1{ 78.0, 24.0, 18.0 };
    CBox box2;
    EXPECT_LT(23.0, box1.volume()); //val1 < val2
}
