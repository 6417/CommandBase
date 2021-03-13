#ifndef COMMANDBASE_PARALLELCOMMANDGROUP_H
#define COMMANDBASE_PARALLELCOMMANDGROUP_H

#include "CommandBase/CommandGroupBase.h"
#include <vector>

namespace fridolinsRobotik
{
    class ParallelCommandGroup : public CommandGroupBase
    {
    private:
        std::vector<CommandBase*> activeCommands;
        std::vector<CommandBase*>::iterator currentCommandIt;
    public:
        unsigned int getNumCommands();
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() override;
    };
}
#endif //COMMANDBASE_PARALLELCOMMANDGROUP_H
