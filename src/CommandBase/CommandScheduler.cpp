#include "CommandBase/CommandScheduler.h"

fridolinsRobotik::CommandScheduler& fridolinsRobotik::CommandScheduler::getInstance()
{
    static auto* instance = new CommandScheduler;
    return *instance;
}

void fridolinsRobotik::CommandScheduler::run()
{
    set<std::shared_ptr<CommandBase>> finishedCommands;
    runAllDefaultCommands();
    for (auto& command : scheduledCommands) {
        if (!command)
            break;
        command->initialize();
        runningCommands.insert(command);
    }
    scheduledCommands.clear();
    for (auto& command : runningCommands)
        runCommand(command, finishedCommands);
    for (auto& finishedCommand : finishedCommands)
        runningCommands.erase(finishedCommand);
}

void fridolinsRobotik::CommandScheduler::schedule(std::shared_ptr<CommandBase> command)
{
    scheduledCommands.insert(std::move(command));
}

void fridolinsRobotik::CommandScheduler::runCommand(const std::shared_ptr<fridolinsRobotik::CommandBase>& command,
                                                    set<std::shared_ptr<CommandBase>>& finishedCommands)
{
    if (command->isFinished())
    {
        endCommand(command, finishedCommands);
        return;
    }
    command->execute();
}

void fridolinsRobotik::CommandScheduler::endCommand(const std::shared_ptr<fridolinsRobotik::CommandBase>& command,
                                                    set<std::shared_ptr<CommandBase>>& finishedCommands)
{
    command->end(false);
    finishedCommands.insert(*runningCommands.find(command));
}

bool fridolinsRobotik::CommandScheduler::hasBeenInitialized(const std::shared_ptr<fridolinsRobotik::CommandBase>& command)
{
    return runningCommands.find(command) != runningCommands.end();
}

void fridolinsRobotik::CommandScheduler::cancelAll()
{
    for (auto& command : runningCommands)
        if (hasBeenInitialized(command))
            command->end(true);
    runningCommands.clear();
    scheduledCommands.clear();
}

void fridolinsRobotik::CommandScheduler::cancel(const std::shared_ptr<fridolinsRobotik::CommandBase>& command)
{
    if (hasBeenInitialized(command))
        command->end(true);
    runningCommands.erase(command);
    scheduledCommands.erase(command);
}

bool fridolinsRobotik::CommandScheduler::isRunning(const std::shared_ptr<CommandBase>& command)
{
    return runningCommands.find(command) != runningCommands.end() || scheduledCommands.find(command) != scheduledCommands.end();
}

void fridolinsRobotik::CommandScheduler::registerSubsystem(const std::shared_ptr<SubsystemBase>& subsystem)
{
    registeredSubsystems.insert(subsystem);
}

bool fridolinsRobotik::CommandScheduler::isSubsystemRegistered(const std::shared_ptr<SubsystemBase>& subsystem)
{
    return registeredSubsystems.find(subsystem) != registeredSubsystems.end();
}

void fridolinsRobotik::CommandScheduler::unregisterSubsystem(const std::shared_ptr<SubsystemBase>& subsystem)
{
    registeredSubsystems.erase(subsystem);
}

void fridolinsRobotik::CommandScheduler::runAllDefaultCommands()
{
    for(auto& subsystem : registeredSubsystems)
    {
        for(auto& command : subsystem->getDefaultCommands())
        {
            schedule(command);
        }
    }
}

fridolinsRobotik::CommandBase::~CommandBase()
{
    fridolinsRobotik::CommandScheduler::getInstance().cancel(std::shared_ptr<CommandBase>(this, [](CommandBase*) {}));
}
