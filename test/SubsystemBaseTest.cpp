#include "SubsystemBaseTest.h"


using namespace test;
using namespace fridolinsRobotik;

void test::SubsystemBaseTest::SetUp()
{
    testSubsystem = TestSubsystem();
    testSubsystem.test = false;
}

TEST_F(SubsystemBaseTest, willSubsystemAfterRegistrationInCommandScheduler)
{
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(&testSubsystem));
    fridolinsRobotik::CommandScheduler::getInstance().registerSubsystem(&testSubsystem);
    ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(&testSubsystem));
}

TEST_F(SubsystemBaseTest, subsystemDestructorTest)
{
    fridolinsRobotik::SubsystemBase *testSubsystemPtr;
    {
        TestSubsystem testSubsystemInScope{};
        testSubsystemPtr = &testSubsystemInScope;
        CommandScheduler::getInstance().registerSubsystem(&testSubsystemInScope);
        ASSERT_TRUE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(&testSubsystemInScope));
    }
    ASSERT_FALSE(fridolinsRobotik::CommandScheduler::getInstance().isSubsystemRegistered(testSubsystemPtr));
}

TEST_F(SubsystemBaseTest, isProgramRinningWithUnregisteredSubsystem)
{

}