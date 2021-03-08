#ifndef COMMANDBASE_COMMANDBASETEST_H
#define COMMANDBASE_COMMANDBASETEST_H

#include "pch.h"

#include "CommandBase/CommandBase.h"
#include "CommandBase/CommandScheduler.h"

namespace test
{
    constexpr int numberOfExecutions = 10;
    class TestCommand : public fridolinsRobotik::CommandBase
    {
    public:
        bool initializedCalled = false;
        int executedCallCount = 0;
        bool endCalled = false;

        void initialize() override;

        void execute() override;

        void end(bool interrupted) override;

        bool isFinished() override;
    };

    class CommandBaseTest : public testing::Test
    {
    public:
        TestCommand testCommand;

        void SetUp() override;
    };
}

#endif //COMMANDBASE_COMMANDBASETEST_H
