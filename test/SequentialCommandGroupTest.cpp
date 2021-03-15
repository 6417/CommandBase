#include "test/SequentialCommandGroupTest.h"
using namespace test::sequentialCommandGroup;
using namespace fridolinsRobotik;

void TestCommand::initialize()
{
    isInitialized = true;
    repetitionsCount = 0;
}

void TestCommand::execute()
{
    repetitionsCount ++;
}

void TestCommand::end(bool interrupted)
{

}

bool TestCommand::isFinished()
{
    return repetitionsCount >= 10;
}

void SequentialCommandGroupTest::SetUp()
{
    command1 = TestCommand();
    command2 = TestCommand();
    commandGroup = TestSequentialCommandGroup();
}

TestSequentialCommandGroup::TestSequentialCommandGroup()
{

}

void SequentialCommandGroupTest::TearDown()
{
    fridolinsRobotik::CommandScheduler::getInstance().cancelAll();
}

TEST_F(SequentialCommandGroupTest, CommandsCorrectlyAdded)
{
    ASSERT_TRUE(commandGroup.getNumCommands() == 0);
    commandGroup.addCommands<2>({test::make_stack_pointer(&command1), test::make_stack_pointer(&command2)});
    ASSERT_TRUE(commandGroup.getNumCommands() == 2);
}

TEST_F(SequentialCommandGroupTest, CommandGroupCorrectlyInitialized)
{
    commandGroup.addCommands<2>({test::make_stack_pointer(& command1), test::make_stack_pointer(& command2)});
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(test::make_stack_pointer(&commandGroup)));
    fridolinsRobotik::CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    fridolinsRobotik::CommandScheduler::getInstance().run();
    ASSERT_TRUE(command1.isInitialized);
}

TEST_F(SequentialCommandGroupTest, CommandGroupSchedulingCommandsCorrectly)
{
    commandGroup.addCommands<2>({test::make_stack_pointer(&command1), test::make_stack_pointer(&command2)});
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isRunning(test::make_stack_pointer(&commandGroup)));
    fridolinsRobotik::CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    for (int i = 0; i < 10; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_TRUE(command1.repetitionsCount == 10);
    ASSERT_TRUE(command1.isFinished() == true);
    ASSERT_FALSE(command2.isInitialized);
    for (int i = 0; i < 5; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_TRUE(command1.repetitionsCount == 10);
    ASSERT_TRUE(command2.repetitionsCount == 5);
    ASSERT_FALSE(command2.isFinished());
}

TEST_F(SequentialCommandGroupTest, CommandGroupCorrectlyFinished)
{
    commandGroup.addCommands<2>({test::make_stack_pointer(&command1), test::make_stack_pointer(&command2)});
    CommandScheduler::getInstance().schedule(test::make_stack_pointer(&commandGroup));
    for (int i = 0; i < 20; i++)
    {
        CommandScheduler::getInstance().run();
    }
    ASSERT_EQ(command1.repetitionsCount, 10);
    ASSERT_EQ(command2.repetitionsCount, 10);
    ASSERT_TRUE(command1.isFinished());
    ASSERT_TRUE(command2.isFinished());
    ASSERT_TRUE(commandGroup.isFinished());
    CommandScheduler::getInstance().run();
    ASSERT_FALSE(CommandScheduler::getInstance().isRunning(test::make_stack_pointer(& commandGroup)));
}
