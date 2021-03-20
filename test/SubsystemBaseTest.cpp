#include "SubsystemBaseTest.h"


using namespace test;
using namespace fridolinsRobotik;

void test::SubsystemBaseTest::SetUp()
{
    testCommand = std::make_shared<TestCommand>();
    testSubsystem1 = std::make_shared<TestSubsystem>();
    testSubsystem2 = std::make_shared<TestSubsystem>();
    testSubsystem1->test = false;
}

RequirementsTestCommand::RequirementsTestCommand(const std::shared_ptr<fridolinsRobotik::SubsystemBase>& subsystem)
{
    addRequirements(subsystem);
}
RequirementsTestCommand::RequirementsTestCommand(const std::set<std::shared_ptr<fridolinsRobotik::SubsystemBase>> subsystems)
{
    addRequirements(subsystems);
}

TEST_F(SubsystemBaseTest, willSubsystemAfterRegistrationBeInCommandScheduler)
{
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(testSubsystem1));
    fridolinsRobotik::CommandScheduler::getInstance().registerSubsystem(testSubsystem1);
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(testSubsystem1));
}

TEST_F(SubsystemBaseTest, subsystemDestructorTest)
{
    fridolinsRobotik::SubsystemBase *testSubsystemPtr;
    {
        TestSubsystem testSubsystemInScope{};
        testSubsystemPtr = &testSubsystemInScope;
        fridolinsRobotik::CommandScheduler::getInstance().registerSubsystem(make_stack_pointer(&testSubsystemInScope));
        ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(make_stack_pointer(&testSubsystemInScope)));
    }
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(make_stack_pointer(testSubsystemPtr)));
}

TEST_F(SubsystemBaseTest, isProgramRinningWithUnregisteredSubsystem)
{
       fridolinsRobotik::CommandScheduler::getInstance().registerSubsystem(testSubsystem1);
       ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(testSubsystem1));
       fridolinsRobotik::CommandScheduler::getInstance().unregisterSubsystem(testSubsystem1);
       ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(testSubsystem1));
}

TEST_F(SubsystemBaseTest, isDefaultCommandInsetDefaultCommandsAfterAdding)
{
    testSubsystem1->addDefaultCommand(testCommand);
    ASSERT_EQ(testSubsystem1->getDefaultCommands().find(testCommand)->get(), testCommand.get());
}

TEST_F(SubsystemBaseTest,  isDefaultCommandRemovedAfterCallingRemoveFunction)
{
    testSubsystem1->addDefaultCommand(testCommand);
    ASSERT_EQ(testSubsystem1->getDefaultCommands().find(testCommand)->get(), testCommand.get());
    testSubsystem1->removeDefaultCommand(testCommand);
    ASSERT_NE(testSubsystem1->getDefaultCommands().find(testCommand)->get(), testCommand.get());
}

TEST_F(SubsystemBaseTest, getRequirementsTest)
{
    std::shared_ptr<RequirementsTestCommand> reqTestCommand = std::make_shared<RequirementsTestCommand>(testSubsystem1);
    ASSERT_EQ(reqTestCommand->getRequirements().find(testSubsystem1)->get(), testSubsystem1.get());
}

TEST_F(SubsystemBaseTest, getMoreThanOneRequirement)
{
   subsystems.insert(testSubsystem1);
   subsystems.insert(testSubsystem2);
   std::shared_ptr<RequirementsTestCommand> reqTestCommand = std::make_shared<RequirementsTestCommand>(subsystems);
   ASSERT_EQ(reqTestCommand->getRequirements().find(testSubsystem1)->get(), testSubsystem1.get());
   ASSERT_EQ(reqTestCommand->getRequirements().find(testSubsystem2)->get(), testSubsystem2.get());
}