#ifndef COMMANDBASE_PARALLELRACECOMMANDGROUP_H
#define COMMANDBASE_PARALLELRACECOMMANDGROUP_H

#include "CommandBase/CommandGroupBase.h"
#include <vector>

namespace fridolinsRobotik
{
    class ParallelRaceCommandGroup : public CommandGroupBase
    {
    private:
        std::vector<CommandBase*> activeCommands;
        std::vector<CommandBase*>::iterator currentCommandIt;
        bool firstCommandFinished;
        void endAllCommands();
    public:
        unsigned int getNumCommands();
        void initialize() override;
        void execute() override;
        void end(bool interrupted) override;
        bool isFinished() override;
    };
}
#endif //COMMANDBASE_PARALLELRACECOMMANDGROUP_H
