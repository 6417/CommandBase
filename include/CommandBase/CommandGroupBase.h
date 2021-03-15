#ifndef COMMANDBASE_COMMANDGROUPBASE_H
#define COMMANDBASE_COMMANDGROUPBASE_H

#include "list"
#include "CommandBase/CommandBase.h"
#include <vector>
#include <array>
#include <memory>

namespace fridolinsRobotik
{
    class CommandGroupBase: public virtual CommandBase
    {
    protected:
        std::vector<std::shared_ptr<CommandBase>> commandsList;
    public:
        CommandGroupBase();

        template<size_t size>
        void addCommands(std::array<std::shared_ptr<CommandBase>, size> commands);

        virtual void initialize() override = 0;
        virtual void execute() override = 0;
        virtual void end(bool interrupted) override = 0;
        virtual bool isFinished() override = 0;
    };
}

template<size_t size>
void fridolinsRobotik::CommandGroupBase::addCommands(std::array<std::shared_ptr<CommandBase>, size> commands)
{
    for (int i = 0; i < size; i++) {
        commandsList.push_back(commands[i]);
    };
}

#endif //COMMANDBASE_COMMANDGROUPBASE_H
