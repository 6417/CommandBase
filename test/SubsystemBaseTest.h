#ifndef COMMANDBASE_SUBSYSTEMBASETEST_H
#define COMMANDBASE_SUBSYSTEMBASETEST_H

#include "test/pch.h"
#include "SubsystemBase/SubsystemBase.h"
#include "CommandBase/CommandScheduler.h"
#include "CommandBaseTest.h"

namespace test
{
    class TestSubsystem : public virtual fridolinsRobotik::SubsystemBase
    {
    public:
        bool test = true;
    };


    class SubsystemBaseTest : public testing::Test
    {
    public:
        std::shared_ptr<TestSubsystem> testSubsystem1;
        std::shared_ptr<TestSubsystem> testSubsystem2;

        std::shared_ptr<TestCommand>  testCommand;

        std::set<std::shared_ptr<fridolinsRobotik::SubsystemBase>> subsystems;

        void SetUp() override;

        std::shared_ptr<TestCommand> command;
    };

    class RequirementsTestCommand : public fridolinsRobotik::CommandBase
    {
    public:
        RequirementsTestCommand(const std::shared_ptr<fridolinsRobotik::SubsystemBase>& subsystem);
        RequirementsTestCommand(const std::set<std::shared_ptr<fridolinsRobotik::SubsystemBase>> subsystems);
    };
}

#endif //COMMANDBASE_SUBSYSTEMBASETEST_H