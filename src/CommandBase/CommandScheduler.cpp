#include "CommandBase/CommandScheduler.h"

fridolinsRobotik::CommandScheduler& fridolinsRobotik::CommandScheduler::getInstance()
{
    static auto* instance = new CommandScheduler;
    return *instance;
}

void fridolinsRobotik::CommandScheduler::run()
{
    std::set < CommandBase * > finishedCommands;
    for (auto& command : scheduledCommands) {
        command->initialize();
        runningCommands.insert(command);
    }
    scheduledCommands.clear();
    for (auto& command : runningCommands)
        runCommand(command, finishedCommands);
    for (auto& finishedCommand : finishedCommands)
        runningCommands.erase(finishedCommand);
}

void fridolinsRobotik::CommandScheduler::schedule(CommandBase* command)
{
    scheduledCommands.insert(command);
}

void fridolinsRobotik::CommandScheduler::runCommand(fridolinsRobotik::CommandBase* command,
                                                    std::set<CommandBase*>& finishedCommands)
{
    if (command->isFinished())
    {
        endCommand(command, finishedCommands);
        return;
    }
    command->execute();
}

void fridolinsRobotik::CommandScheduler::endCommand(fridolinsRobotik::CommandBase* command,
                                                    std::set<CommandBase*>& finishedCommands)
{
    command->end(false);
    finishedCommands.insert(*runningCommands.find(command));
}

bool fridolinsRobotik::CommandScheduler::hasBeenInitialized(fridolinsRobotik::CommandBase* command)
{
    return runningCommands.find(command) != runningCommands.end();
}

void fridolinsRobotik::CommandScheduler::cancelAll()
{
    for (auto& command : runningCommands)
        if (hasBeenInitialized(command))
            command->end(true);
    runningCommands.clear();
}

void fridolinsRobotik::CommandScheduler::cancel(fridolinsRobotik::CommandBase* command)
{
    if (hasBeenInitialized(command))
        command->end(true);
    runningCommands.erase(command);
    scheduledCommands.erase(command);
}

bool fridolinsRobotik::CommandScheduler::isRunning(fridolinsRobotik::CommandBase* command)
{
    return runningCommands.find(command) != runningCommands.end();
}
