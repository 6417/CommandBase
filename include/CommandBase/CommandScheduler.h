#ifndef COMMANDBASE_COMMANDSCHEDULER_H
#define COMMANDBASE_COMMANDSCHEDULER_H

#include "CommandBase/pch.h"
#include "CommandBase/CommandBase.h"
#include "utilities/set.h"

namespace fridolinsRobotik
{
    class CommandScheduler
    {
    private:
        set<std::shared_ptr<CommandBase>> runningCommands;
        set<std::shared_ptr<CommandBase>> scheduledCommands;

        void runCommand(const std::shared_ptr<CommandBase>& command, set<std::shared_ptr<CommandBase>>& finishedCommands);

        void endCommand(const std::shared_ptr<fridolinsRobotik::CommandBase>& command,
                        set<std::shared_ptr<CommandBase>>& finishedCommands);

    public:
        static CommandScheduler& getInstance();

        void run();

        void schedule(std::shared_ptr<CommandBase> command);

        void cancelAll();

        void cancel(const std::shared_ptr<CommandBase>& command);

        bool hasBeenInitialized(std::shared_ptr<CommandBase> command);

        bool isRunning(const std::shared_ptr<CommandBase>& command);
    };
}

#endif //COMMANDBASE_COMMANDSCHEDULER_H
