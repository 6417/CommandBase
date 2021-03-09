#ifndef COMMANDBASE_COMMANDBASE_H
#define COMMANDBASE_COMMANDBASE_H

#include "CommandBase/pch.h"

namespace fridolinsRobotik
{
    class CommandScheduler;
    class CommandBase
    {
    public:
        virtual void initialize();

        virtual void execute();

        virtual void end(bool interrupted);

        virtual bool isFinished();

        ~CommandBase();
    };
}

#endif //COMMANDBASE_COMMANDBASE_H
