#ifndef COMMANDBASE_SUBSYSTEMBASE_H
#define COMMANDBASE_SUBSYSTEMBASE_H

#include "SubsystemBase/pch.h"
#include "CommandBase/CommandBase.h"

namespace fridolinsRobotik
{
    class SubsystemBase
    {
    private:

        std::set<std::shared_ptr<CommandBase>> defaultCommands;

    public:
        virtual void periodic();

        ~SubsystemBase();

        void addDefaultCommand(std::shared_ptr<fridolinsRobotik::CommandBase> command);

        std::set<std::shared_ptr<fridolinsRobotik::CommandBase>> getDefaultCommands();

        void removeDefaultCommand(std::shared_ptr<CommandBase> command);
    };
}

#endif //COMMANDBASE_SUBSYSTEMBASE_H