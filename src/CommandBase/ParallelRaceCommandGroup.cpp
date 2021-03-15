#include "CommandBase/ParallelRaceCommandGroup.h"

using namespace fridolinsRobotik;

unsigned int ParallelRaceCommandGroup::getNumCommands()
{
    return commandsList.size();
}

void ParallelRaceCommandGroup::initialize()
{
    activeCommands = commandsList;
    currentCommandIt = commandsList.begin();
    firstCommandFinished = false;

    if (currentCommandIt == commandsList.end()) return;

    while (currentCommandIt != commandsList.end())
    {
        (*currentCommandIt)->initialize();
        currentCommandIt++;
    }
}

void ParallelRaceCommandGroup::execute()
{
    currentCommandIt = activeCommands.begin();

    while (currentCommandIt != activeCommands.end())
    {
        if ((*currentCommandIt)->isFinished())
        {
            firstCommandFinished = true;
            activeCommands.erase(currentCommandIt);
            endAllCommands();
            return;
        }
        else
        {
            (*currentCommandIt)->execute();
        }
        currentCommandIt++;
    }
}

void ParallelRaceCommandGroup::end(bool interrupted)
{

}

bool ParallelRaceCommandGroup::isFinished()
{
    return firstCommandFinished;
}

void ParallelRaceCommandGroup::endAllCommands()
{
    currentCommandIt = activeCommands.begin();
    while (currentCommandIt != activeCommands.end())
    {
        (*currentCommandIt)->end(true);
        currentCommandIt++;
    }
}
