#ifndef COMMANDBASE_COMMANDSCHEDULER_H
#define COMMANDBASE_COMMANDSCHEDULER_H


#include "CommandBase/pch.h"
#include "CommandBase/CommandBase.h"
#include "SubsystemBase/SubsystemBase.h"

namespace fridolinsRobotik
{
    using namespace std;
    class CommandScheduler
    {
    private:
        std::set<std::shared_ptr<CommandBase>> runningCommands;
        std::set<std::shared_ptr<CommandBase>> scheduledCommands;
        std::set<std::shared_ptr<SubsystemBase>> registeredSubsystems;
        std::map<std::shared_ptr<SubsystemBase>, std::shared_ptr<CommandBase>> runningCommandsWithRequirements;

        void runCommand(const std::shared_ptr<CommandBase>& command, set<std::shared_ptr<CommandBase>>& finishedCommands);

        void endCommand(const std::shared_ptr<fridolinsRobotik::CommandBase>& command,
                        set<std::shared_ptr<CommandBase>>& finishedCommands);

        void runAllDefaultCommands();


    public:
        static CommandScheduler& getInstance();

        void run();

        void schedule(const std::shared_ptr<CommandBase>& command);

        void cancelAll();

        void cancel(const std::shared_ptr<CommandBase>& command);

        bool hasBeenInitialized(const std::shared_ptr<CommandBase>& command);

        bool isRunning(const std::shared_ptr<CommandBase>& command);

        void registerSubsystem(const std::shared_ptr<SubsystemBase>& subsystem);

        bool isSubsystemRegistered(const std::shared_ptr<SubsystemBase>& subsystem);

        void unregisterSubsystem(const std::shared_ptr<SubsystemBase>& subsystem);
    };
}

#endif //COMMANDBASE_COMMANDSCHEDULER_H
