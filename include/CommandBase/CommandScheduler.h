#ifndef COMMANDBASE_COMMANDSCHEDULER_H
#define COMMANDBASE_COMMANDSCHEDULER_H

#include "CommandBase/pch.h"
#include "CommandBase/CommandBase.h"

namespace fridolinsRobotik
{
    class CommandScheduler
    {
    private:
        std::vector<CommandBase*> runningCommands;
        void runCommand(CommandBase* command);
        void endCommand(CommandBase* command);
    public:
        static CommandScheduler& getInstance();

        void run();
        void schedule(CommandBase* command);
    };
}

#endif //COMMANDBASE_COMMANDSCHEDULER_H
