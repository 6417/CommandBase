#include <gtest/gtest.h>
#include "CommandBase/library.h"

TEST(helloWorld, test) {
    hello();
    ASSERT_TRUE(true);
}

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
}
