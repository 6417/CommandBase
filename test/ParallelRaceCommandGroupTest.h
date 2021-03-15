#ifndef COMMANDBASE_PARALLELRACECOMMANDGROUPTEST_H
#define COMMANDBASE_PARALLELRACECOMMANDGROUPTEST_H

#include "test/pch.h"
#include "CommandBase/ParallelRaceCommandGroup.h"
#include "CommandBase/CommandBase.h"
#include "CommandBase/CommandScheduler.h"

namespace test::raceCommandGroupTest
{
    class TestParallelRaceCommandGroup: public fridolinsRobotik::ParallelRaceCommandGroup
    {
    public:
        TestParallelRaceCommandGroup();
    };

    class TestCommand : public fridolinsRobotik::CommandBase
    {
    private:
        bool finished = false;
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

    class ParallelRaceCommandGroupTest : public testing::Test
    {
    public:
        std::shared_ptr<TestCommand> command1;
        std::shared_ptr<TestCommand> command2;
        TestParallelRaceCommandGroup commandGroup;

        void SetUp() override;
        void TearDown() override;
    };
}
#endif //COMMANDBASE_PARALLELRACECOMMANDGROUPTEST_H
