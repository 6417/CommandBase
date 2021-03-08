#include "CommandBaseTest.h"

using namespace test;

int TestCommand::executedCallCount = 0;

void test::CommandBaseTest::SetUp()
{
    test::TestCommand::executedCallCount = 0;
    testCommand = TestCommand();
}

void CommandBaseTest::TearDown()
{
    fridolinsRobotik::CommandScheduler::getInstance().cancelAll();
}


void test::TestCommand::initialize()
{
    fridolinsRobotik::CommandBase::initialize();
    initializedCalled = true;
    m_executionCallCount = 0;
}

void test::TestCommand::execute()
{
    executedCallCount++;
    m_executionCallCount++;
}

void test::TestCommand::end(bool interrupted)
{
    fridolinsRobotik::CommandBase::end(interrupted);
    endCalled = true;
    interruptedEnd = interrupted;
}

bool test::TestCommand::isFinished()
{
    return m_executionCallCount >= numberOfExecutions - 1;
}

TestCommand::~TestCommand()
{
    fridolinsRobotik::CommandBase::~CommandBase();
}

TEST_F(CommandBaseTest, SchedulerCallsAllFunctionsCorrectly)
{
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    ASSERT_FALSE(testCommand.initializedCalled);
    ASSERT_FALSE(testCommand.endCalled);
    ASSERT_EQ(testCommand.executedCallCount, 0);
    for (int i = 0; i < numberOfExecutions; i++)
        fridolinsRobotik::CommandScheduler::getInstance().run();
    ASSERT_TRUE(testCommand.initializedCalled);
    ASSERT_TRUE(testCommand.endCalled);
    ASSERT_EQ(testCommand.executedCallCount, numberOfExecutions - 1);
}

TEST_F(CommandBaseTest, SchedulerCallsAllFunctionsWhenCommandIsScheduledMultipleTimes)
{
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    for (int i = 0; i < numberOfExecutions; i++)
    {
        fridolinsRobotik::CommandScheduler::getInstance().run();
        if (i < numberOfExecutions - 1)
            ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    }
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    test::TestCommand::executedCallCount = 0;
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    for (int i = 0; i < numberOfExecutions; i++)
    {
        fridolinsRobotik::CommandScheduler::getInstance().run();
        if (i < numberOfExecutions - 1)
            ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    }
    ASSERT_EQ(testCommand.executedCallCount, numberOfExecutions - 1);
}

TEST_F(CommandBaseTest, SchedulerCallsMultipleCommandsCorrectly)
{
    for (int i = 0; i < numberOfCommands; i++)
        commands.emplace_back(TestCommand());
    for (auto& command : commands)
        fridolinsRobotik::CommandScheduler::getInstance().schedule(&command);
    fridolinsRobotik::CommandScheduler::getInstance().run();
    ASSERT_EQ(TestCommand::executedCallCount, numberOfCommands);
}

TEST_F(CommandBaseTest, ScheduleSameFunctionTwice_isCommandExecutedCorrectly)
{
    for (int i = 0; i < 2; i++)
    {
        fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
        fridolinsRobotik::CommandScheduler::getInstance().run();
    }
    ASSERT_EQ(testCommand.executedCallCount, 2);
    ASSERT_TRUE(testCommand.initializedCalled);
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
}

TEST_F(CommandBaseTest, CancelAll_WillCallEndFunctionCorrectly)
{
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    fridolinsRobotik::CommandScheduler::getInstance().run();
    fridolinsRobotik::CommandScheduler::getInstance().cancelAll();
    ASSERT_TRUE(testCommand.endCalled);
    ASSERT_TRUE(testCommand.interruptedEnd);
}