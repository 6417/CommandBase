#ifndef COMMANDBASE_SETTEST_H
#define COMMANDBASE_SETTEST_H

#include "test/pch.h"

#include "utilities/set.h"

namespace test
{
    class SetTest : public testing::Test
    {
    public:
        set<int> testSet;
        void SetUp();
    };
}

#endif //COMMANDBASE_SETTEST_H

