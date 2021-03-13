#include "CommandBase/ParallelCommandGroup.h"

using namespace fridolinsRobotik;

unsigned int ParallelCommandGroup::getNumCommands()
{
    return commandsList.size();
}

void ParallelCommandGroup::initialize()
{
    activeCommands = commandsList;
    currentCommandIt = activeCommands.begin();

    if (currentCommandIt == activeCommands.end()) return;

    while (currentCommandIt != activeCommands.end())
    {
        (*currentCommandIt)->initialize();
        currentCommandIt++;
    }
}

void ParallelCommandGroup::execute()
{
    currentCommandIt = activeCommands.begin();

    if (currentCommandIt == activeCommands.end()) return;

    while (currentCommandIt != activeCommands.end())
    {
        if ((*currentCommandIt)->isFinished())
        {
            (*currentCommandIt)->end(false);
            activeCommands.erase(currentCommandIt);
            currentCommandIt--;
        }
        else (*currentCommandIt)->execute();

        currentCommandIt++;
    }
}

void ParallelCommandGroup::end(bool interrupted)
{

}

bool ParallelCommandGroup::isFinished()
{
    return activeCommands.size() == 0;
}