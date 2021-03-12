#ifndef COMMANDBASE_SUBSYSTEMBASE_H
#define COMMANDBASE_SUBSYSTEMBASE_H
#include "SubsystemBase/pch.h"
#include "CommandBase/CommandScheduler.h"

namespace fridolinsRobotik
{
    class SubsystemBase
    {
    public:
        virtual void periodic();
        ~SubsystemBase();
    };
}
#endif //COMMANDBASE_SUBSYSTEMBASE_H
