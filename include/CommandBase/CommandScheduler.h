#ifndef COMMANDBASE_COMMANDSCHEDULER_H
#define COMMANDBASE_COMMANDSCHEDULER_H

#include "CommandBase/pch.h"
#include "CommandBase/CommandBase.h"

namespace fridolinsRobotik
{
    class CommandScheduler
    {
    private:
        std::set<CommandBase*> runningCommands;
        std::set<CommandBase*> scheduledCommands;

        void runCommand(CommandBase* command, std::set<CommandBase*>& finishedCommands);

        void endCommand(fridolinsRobotik::CommandBase* command,
                        std::set<CommandBase*>& finishedCommands);

    public:
        static CommandScheduler& getInstance();

        void run();

        void schedule(CommandBase* command);

        void cancelAll();

        void cancel(CommandBase* command);

        bool hasBeenInitialized(CommandBase* command);

        bool isRunning(CommandBase* command);
    };
}

#endif //COMMANDBASE_COMMANDSCHEDULER_H
