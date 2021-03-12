#ifndef COMMANDBASE_SUBSYSTEMBASETEST_H
#define COMMANDBASE_SUBSYSTEMBASETEST_H

#include "test/pch.h"
#include "SubsystemBase/SubsystemBase.h"
#include "CommandBase/CommandScheduler.h"

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
        TestSubsystem testSubsystem;
        void SetUp() override;

    };
}

#endif //COMMANDBASE_SUBSYSTEMBASETEST_H
