#ifndef COMMANDBASE_PARALLELCOMMANDGROUPTEST_H
#define COMMANDBASE_PARALLELCOMMANDGROUPTEST_H

#include "test/pch.h"
#include "CommandBase/ParallelCommandGroup.h"
#include "CommandBase/CommandBase.h"
#include "CommandBase/CommandScheduler.h"

namespace test::parallelCommandGroup
{

    class TestCommand : public fridolinsRobotik::CommandBase
    {
    public:
        TestCommand(int repetitions);
        bool isInitialized = false;
        int repetitionsCount = 0;
        int finishedAfterRepetitions;
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished()override;
    };

    class TestParallelCommandGroup : public fridolinsRobotik::ParallelCommandGroup
    {
    public:
        TestParallelCommandGroup();
    };

    class ParallelCommandGroupTest : public testing::Test
    {
    public:
        TestCommand* command1;
        TestCommand* command2;
        TestParallelCommandGroup commandGroup;

        void SetUp() override;

        void TearDown() override;
    };

}

#endif //COMMANDBASE_PARALLELCOMMANDGROUPTEST_H
