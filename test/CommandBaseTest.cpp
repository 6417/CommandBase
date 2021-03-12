#include "test/CommandBaseTest.h"

using namespace test;
using fridolinsRobotik::CommandScheduler;

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

TEST_F(CommandBaseTest, CancelCommand_WillEndBeCalledCorrectly)
{
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    fridolinsRobotik::CommandScheduler::getInstance().run();
    fridolinsRobotik::CommandScheduler::getInstance().cancel(&testCommand);
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_TRUE(testCommand.endCalled);
    ASSERT_TRUE(testCommand.interruptedEnd);
}

TEST_F(CommandBaseTest, DestructCommand_WillCommandBeCanceldInCommandScheduler)
{
    fridolinsRobotik::CommandBase* testCommandPtr;
    {
        TestCommand testCommandInScope{};
        testCommandPtr = &testCommandInScope;
        fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommandInScope);
        fridolinsRobotik::CommandScheduler::getInstance().run();
        ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommandInScope));
    }
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(testCommandPtr));
}

TEST_F(CommandBaseTest, CommandSchedulerIsRunningAndHasBeenInitialized_WillReturnRightResults)
{
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    fridolinsRobotik::CommandScheduler::getInstance().run();
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    fridolinsRobotik::CommandScheduler::getInstance().cancel(&testCommand);
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
}

TEST_F(CommandBaseTest, CommandSchedulerCancelAll_WillCancelAllCommandCancelCommandsCorrectly)
{
    TestCommand testCommand1{};
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand1));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand1));

    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand);
    fridolinsRobotik::CommandScheduler::getInstance().schedule(&testCommand1);
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand1));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand1));

    fridolinsRobotik::CommandScheduler::getInstance().run();
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand1));
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand1));

    fridolinsRobotik::CommandScheduler::getInstance().cancelAll();
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(&testCommand1));
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().hasBeenInitialized(&testCommand1));
}

TEST_F(CommandBaseTest, CancelCommandThatsNotRunning)
{
    fridolinsRobotik::CommandScheduler::getInstance().cancel(&testCommand);
    ASSERT_FALSE(testCommand.endCalled);
    ASSERT_FALSE(testCommand.interruptedEnd);
}

TEST_F(CommandBaseTest, CancelCommandOnMemoryThatDoesntExist_WontCauseSIGSEV)
{
    auto* notExistingCommand = new TestCommand;
    delete notExistingCommand;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointers"
    CommandScheduler::getInstance().schedule(notExistingCommand);
    CommandScheduler::getInstance().schedule(nullptr);
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(notExistingCommand));
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(nullptr));
    fridolinsRobotik::CommandScheduler::getInstance().cancel(notExistingCommand);
    fridolinsRobotik::CommandScheduler::getInstance().cancel(nullptr);
    ASSERT_FALSE(CommandScheduler::getInstance().isRunning(notExistingCommand));
    ASSERT_FALSE(CommandScheduler::getInstance().isRunning(nullptr));
#pragma clang diagnostic pop
}

TEST_F(CommandBaseTest, CancelAllCommandOnMemoryThatDoesntExist_WontCauseSIGSEV)
{
    auto* notExistingCommand = new TestCommand;
    delete notExistingCommand;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointers"
    CommandScheduler::getInstance().schedule(notExistingCommand);
    CommandScheduler::getInstance().schedule(nullptr);
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(notExistingCommand));
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(nullptr));
    CommandScheduler::getInstance().cancelAll();
    ASSERT_FALSE(CommandScheduler::getInstance().isRunning(notExistingCommand));
    ASSERT_FALSE(CommandScheduler::getInstance().isRunning(nullptr));
#pragma clang diagnostic pop
}
