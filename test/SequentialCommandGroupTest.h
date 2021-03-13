#ifndef COMMANDBASE_SEQUENTIALCOMMANDGROUPTEST_H
#define COMMANDBASE_SEQUENTIALCOMMANDGROUPTEST_H

#include "test/pch.h"
#include "CommandBase/SequentialCommandGroup.h"
#include "CommandBase/CommandBase.h"
#include "CommandBase/CommandScheduler.h"

namespace test::sequentialCommandGroup
{

class TestCommand : public fridolinsRobotik::CommandBase
{
public:
    bool isInitialized = false;
    int repetitionsCount = 0;
    void initialize() override;
    void execute() override;
    void end(bool interrupted) override;
    bool isFinished()override;
};

class TestSequentialCommandGroup : public fridolinsRobotik::SequentialCommandGroup
{
public:
    TestSequentialCommandGroup();
};

    class SequentialCommandGroupTest : public testing::Test
    {
    public:
        TestCommand command1;
        TestCommand command2;
        TestSequentialCommandGroup commandGroup;

        void SetUp() override;

        void TearDown() override;
    };

}

#endif //COMMANDBASE_SEQUENTIALCOMMANDGROUPTEST_H
