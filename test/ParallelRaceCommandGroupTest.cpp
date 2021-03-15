#include "test/ParallelRaceCommandGroupTest.h"

using namespace test::raceCommandGroupTest;
using namespace fridolinsRobotik;

void ParallelRaceCommandGroupTest::SetUp()
{
    commandGroup = TestParallelRaceCommandGroup();
    command1 = std::make_shared<TestCommand>(TestCommand(5));
    command2 = std::make_shared<TestCommand>(TestCommand(10));
}

void ParallelRaceCommandGroupTest::TearDown()
{
   CommandScheduler::getInstance().cancelAll();
}

TestCommand::TestCommand(int repetitions)
{
    finishedAfterRepetitions = repetitions;
}

void TestCommand::initialize()
{
    repetitionsCount = 0;
    isInitialized = true;
    finished = false;
}

void TestCommand::execute()
{
    repetitionsCount++;
}

void TestCommand::end(bool interrupted)
{

}

bool TestCommand::isFinished()
{
    return repetitionsCount == finishedAfterRepetitions ;
}

TestParallelRaceCommandGroup::TestParallelRaceCommandGroup()
{

}

TEST_F(ParallelRaceCommandGroupTest, CommandsWorkingCorrectly)
{
    command1->initialize();
    command1->execute();
    ASSERT_EQ(command1->isInitialized, true);
    ASSERT_EQ(command1->repetitionsCount, 1);
}

TEST_F(ParallelRaceCommandGroupTest, CommandsCorrectlyAdded)
{
    ASSERT_EQ(commandGroup.getNumCommands(), 0);
    commandGroup.addCommands<2>({command1, command2});
    ASSERT_EQ(commandGroup.getNumCommands(), 2);
}

TEST_F(ParallelRaceCommandGroupTest, CommandGroupCorrectlyInitialized)
{
    commandGroup.addCommands<2>({command1, command2});
    ASSERT_EQ(commandGroup.getNumCommands(), 2);
    CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    ASSERT_TRUE(CommandScheduler::getInstance().isRunning(test::make_stack_pointer(&commandGroup)));
}

TEST_F(ParallelRaceCommandGroupTest, CommandsCorrectlyInitialized)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    CommandScheduler::getInstance().run();
    ASSERT_TRUE(command1->isInitialized);
    ASSERT_TRUE(command2->isInitialized);
}

TEST_F(ParallelRaceCommandGroupTest, CommandsCorrectlyScheduled)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    for (int i = 0; i < 10; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_TRUE(command1->isInitialized);
    ASSERT_TRUE(command2->isInitialized);
    ASSERT_EQ(command1->repetitionsCount, 5);
    ASSERT_EQ(command2->repetitionsCount, 5);
    ASSERT_TRUE(command1->isFinished());
    ASSERT_FALSE(command2->isFinished());
}

TEST_F(ParallelRaceCommandGroupTest, CommandGroupDeletedCorrectly)
{
    commandGroup.addCommands<2>({command1, command2});
    CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    for (int i = 0; i < 11; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_EQ(command1->repetitionsCount, 5);
    ASSERT_EQ(command2->repetitionsCount, 5);
    ASSERT_TRUE(commandGroup.isFinished());
    CommandScheduler::getInstance().isRunning(test::make_stack_pointer(&commandGroup));
}
