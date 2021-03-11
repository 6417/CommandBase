#include "test/utilities/setTest.h"

using namespace test;

void test::SetTest::SetUp()
{
    testSet = set<int>{};
}

TEST_F(SetTest, Insert_WillElementBeAdded)
{
    int value = 1;
    testSet.insert(value);
    ASSERT_EQ(testSet.getElementList().getSize(), 1);
    ASSERT_EQ(testSet.getElementList()[0], value);
}

TEST_F(SetTest, Constructor_WillElementListsSizeBeZero)
{
    ASSERT_EQ(testSet.getElementList().getSize(), 0);
}

TEST_F(SetTest, InsertSameElementTwice_WillOnlyOnlyOneBeInSet)
{
    int value = 1;
    testSet.insert(value);
    testSet.insert(value);
    ASSERT_EQ(testSet.getElementList().getSize(), 1);
    ASSERT_EQ(testSet.getElementList()[0], value);
}


TEST_F(SetTest, EreaseElementNotInList)
{
    testSet.erase(1);
    ASSERT_EQ(testSet.getSize(), 0);
}
