#include "pch.h"
#include "CommandBase/library.h"

TEST(helloWorld, test) {
    hello();
    ASSERT_TRUE(true);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
