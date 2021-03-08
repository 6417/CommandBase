#include "CommandBase/CommandScheduler.h"

fridolinsRobotik::CommandScheduler& fridolinsRobotik::CommandScheduler::getInstance()
{
    static auto* instance = new CommandScheduler;
    return *instance;
}

void fridolinsRobotik::CommandScheduler::run()
{
    for (auto command : runningCommands)
        runCommand(command);
}

void fridolinsRobotik::CommandScheduler::schedule(CommandBase* command)
{
    runningCommands.push_back(command);
}

void fridolinsRobotik::CommandScheduler::runCommand(fridolinsRobotik::CommandBase* command)
{
    if (!command->hasBeenInitialized())
        command->initialize();
    if (command->isFinished())
    {
        endCommand(command);
        return;
    }
    command->execute();
}

void fridolinsRobotik::CommandScheduler::endCommand(fridolinsRobotik::CommandBase* command)
{
    command->end(false);
    for (auto it = runningCommands.begin();
         it < this->runningCommands.end(); it++)
        if (*it == command)
            this->runningCommands.erase(it);
}
