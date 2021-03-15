#ifndef COMMANDBASE_COMMANDBASETEST_H
#define COMMANDBASE_COMMANDBASETEST_H

#include "test/pch.h"

#include "CommandBase/CommandBase.h"

#include "CommandBase/CommandScheduler.h"

namespace test
{
    constexpr int numberOfExecutions = 10;
    constexpr int numberOfCommands = 20;

    class TestCommand : public fridolinsRobotik::CommandBase
    {
    public:
        bool initializedCalled = false;
        static int executedCallCount;
        int m_executionCallCount = 0;
        bool endCalled = false;
        bool interruptedEnd;

        void initialize() override;

        void execute() override;

        void end(bool interrupted) override;

        bool isFinished() override;

        ~TestCommand();
    };

    class CommandBaseTest : public testing::Test
    {
    public:
        std::shared_ptr<TestCommand> testCommand;
        std::vector<TestCommand> commands;

        void SetUp() override;

        void TearDown() override;
    };

    template<typename T>
    std::shared_ptr<T> make_stack_pointer(T* ptr);
}

#endif //COMMANDBASE_COMMANDBASETEST_H
