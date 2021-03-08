#include "CommandBaseTest.h"

using namespace test;

void test::CommandBaseTest::SetUp()
{

}

void test::TestCommand::initialize()
{
    fridolinsRobotik::CommandBase::initialize();
    initializedCalled = true;
}

void test::TestCommand::execute()
{
    executedCallCount++;
}

void test::TestCommand::end(bool interrupted)
{
    fridolinsRobotik::CommandBase::end(interrupted);
    endCalled = true;
}

bool test::TestCommand::isFinished()
{
    return executedCallCount >= numberOfExecutions - 1;
}

TEST_F(CommandBaseTest, SchedulerCallsAllFunctionsCorrectly)
{
    ASSERT_FALSE(testCommand.initializedCalled);
    ASSERT_FALSE(testCommand.endCalled);
    ASSERT_EQ(testCommand.executedCallCount, 0);
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
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
            ASSERT_TRUE(testCommand.hasBeenInitialized());
    }
    ASSERT_FALSE(testCommand.hasBeenInitialized());
    testCommand.executedCallCount = 0;
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    for (int i = 0; i < numberOfExecutions; i++)
    {
        fridolinsRobotik::CommandScheduler::getInstance().run();
        if (i < numberOfExecutions - 1)
            ASSERT_TRUE(testCommand.hasBeenInitialized());
    }
    ASSERT_EQ(testCommand.executedCallCount, numberOfExecutions - 1);
}