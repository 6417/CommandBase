#include "ParallelCommandGroupTest.h"
using namespace test::parallelCommandGroup;
using namespace fridolinsRobotik;

void TestCommand::initialize()
{
    isInitialized = true;
}

void TestCommand::execute()
{
    repetitionsCount++;
}

void TestCommand::end(bool interrupted)
{
    CommandBase::end(interrupted);
}

bool TestCommand::isFinished()
{
    return repetitionsCount == finishedAfterRepetitions;
}

TestCommand::TestCommand(int repetitions)
{
    finishedAfterRepetitions = repetitions;
}

TestParallelCommandGroup::TestParallelCommandGroup()
{

}

void ParallelCommandGroupTest::SetUp()
{
    command1 = new TestCommand(5);
    command2 = new TestCommand(10);
    commandGroup = TestParallelCommandGroup();
}

void ParallelCommandGroupTest::TearDown()
{
    CommandScheduler::getInstance().cancelAll();
    delete command1;
    delete command2;
}

TEST_F(ParallelCommandGroupTest, CommandsWorkingCorrectly)
{
    command1->initialize();
    command1->execute();
    ASSERT_EQ(command1->isInitialized, true);
    ASSERT_EQ(command1->repetitionsCount, 1);
}

TEST_F(ParallelCommandGroupTest, CommandsCorrectlyAdded)
{
    ASSERT_EQ(commandGroup.getNumCommands(), 0);
    commandGroup.addCommands<2>({command1, command2});
    ASSERT_EQ(commandGroup.getNumCommands(), 2);
}

TEST_F(ParallelCommandGroupTest, CommandGroupCorrectlyInitialized)
{
    commandGroup.addCommands<2>({command1, command2});
    ASSERT_EQ(commandGroup.getNumCommands(), 2);
    CommandScheduler::getInstance().schedule(&commandGroup);
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(&commandGroup));
}

TEST_F(ParallelCommandGroupTest, CommandsCorrectlyInitialized)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(&commandGroup);
    CommandScheduler::getInstance().run();
    ASSERT_TRUE(command1->isInitialized);
    ASSERT_TRUE(command2->isInitialized);
}

TEST_F(ParallelCommandGroupTest, CommandsCorrectlyScheduled)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(&commandGroup);
    for (int i = 0; i < 10; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_TRUE(command1->isInitialized);
    ASSERT_TRUE(command2->isInitialized);
    ASSERT_TRUE(command1->isFinished());
    ASSERT_TRUE(command2->isFinished());
    ASSERT_EQ(command1->repetitionsCount, 5);
    ASSERT_EQ(command2->repetitionsCount, 10);
}

TEST_F(ParallelCommandGroupTest, CommandGroupDeletedCorrectly)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(&commandGroup);
    for (int i = 0; i < 11; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_EQ(command1->repetitionsCount, 5);
    ASSERT_EQ(command2->repetitionsCount, 10);
    ASSERT_TRUE(commandGroup.isFinished());
    CommandScheduler::getInstance().isRunning(&commandGroup);
}