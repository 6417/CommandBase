#include "CommandBase/SequentialCommandGroup.h"

using namespace fridolinsRobotik;

void SequentialCommandGroup::initialize()
{
    runningCommandIt = commandsList.begin();
    if (runningCommandIt == commandsList.end()) return;
    (*runningCommandIt)->initialize();
}

void SequentialCommandGroup::execute()
{
    if ((*runningCommandIt)->isFinished()) {
        (*runningCommandIt)->end(false);
        runningCommandIt++;
    }
    (*runningCommandIt)->execute();
}

void SequentialCommandGroup::end(bool interrupted)
{

}

bool SequentialCommandGroup::isFinished()
{
    return commandsList.back()->isFinished();
}

int SequentialCommandGroup::getNumCommands()
{
    return commandsList.size();
}
