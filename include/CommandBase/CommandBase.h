#ifndef COMMANDBASE_COMMANDBASE_H
#define COMMANDBASE_COMMANDBASE_H

#include "CommandBase/pch.h"

namespace fridolinsRobotik
{
    class CommandScheduler;

    class CommandBase
    {
    private:
        bool initialized = false;
    public:
        bool hasBeenInitialized();
        virtual void initialize();

        virtual void execute();

        virtual void end(bool interrupted);

        virtual bool isFinished();
    };
}

#endif //COMMANDBASE_COMMANDBASE_H
