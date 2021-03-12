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

TEST_F(SetTest, FindElementWillReturnCorrectIterator)
{
    constexpr int valueToFind = -1;
    for (int i = 0; i < 100; i++)
        testSet.insert(i);
    testSet.insert(valueToFind);
    ASSERT_NE(testSet.find(valueToFind), testSet.end());
    ASSERT_EQ(*testSet.find(valueToFind), valueToFind);
}

TEST_F(SetTest, FindElementWichIsNotInSetReturnEndIterator)
{
    constexpr int valueToFind = -1;
    for (int i = 0; i < 100; i++)
        testSet.insert(i);
    ASSERT_EQ(testSet.find(valueToFind), testSet.end());
}

TEST_F(SetTest, ClearEmptySetWillSizeStillBeZero)
{
    testSet.clear();
    ASSERT_EQ(testSet.getSize(), 0);
}

TEST_F(SetTest, BeginIteratorWillPointToFirstElement)
{
    constexpr int firstValue = 1;
    testSet.insert(firstValue);
    ASSERT_EQ(*testSet.begin(), firstValue);
    ASSERT_EQ(&(*testSet.begin()), &testSet.getElementList()[0]);
}

TEST_F(SetTest, EmptySet_AreBeginAndEndIteratorsEqual)
{
    ASSERT_EQ(testSet.begin(), testSet.end());
}