#ifndef COMMANDBASE_SEQUENTIALCOMMANDGROUP_H
#define COMMANDBASE_SEQUENTIALCOMMANDGROUP_H

#include "CommandGroupBase.h"
#include "CommandBase/CommandScheduler.h"

namespace fridolinsRobotik
{
    class SequentialCommandGroup : public fridolinsRobotik::CommandGroupBase
    {
    private:
        //Iterator<CommandBase*> runningCommandIt;
        std::vector<std::shared_ptr<CommandBase>>::iterator runningCommandIt;
        bool finished = false;
    public:
        void initialize() override;

        void execute() override;

        void end(bool interrupted) override;

        bool isFinished() override;

        int getNumCommands();
    };
}
#endif //COMMANDBASE_SEQUENTIALCOMMANDGROUP_H
