#ifndef COMMANDBASE_COMMANDBASE_H
#define COMMANDBASE_COMMANDBASE_H

#include "CommandBase/pch.h"

namespace fridolinsRobotik
{
    class CommandBase
    {
    private:

        std::set<std::shared_ptr<SubsystemBase>> requirements;

    protected:

        void addRequirements(std::shared_ptr<SubsystemBase> subsystem);

        void addRequirements(std::set<std::shared_ptr<SubsystemBase>> subsystems);

    public:
        virtual void initialize();

        virtual void execute();

        virtual void end(bool interrupted);

        virtual bool isFinished();

        bool hasRequirements();

        ~CommandBase();

        std::set<std::shared_ptr<fridolinsRobotik::SubsystemBase>> getRequirements();
    };
}

#endif //COMMANDBASE_COMMANDBASE_H
