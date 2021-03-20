#include <SubsystemBase/SubsystemBase.h>
#include "CommandBase/CommandScheduler.h"

using namespace fridolinsRobotik;
void SubsystemBase::periodic()
{
}

SubsystemBase::~SubsystemBase()
{
   CommandScheduler::getInstance().unregisterSubsystem(std::shared_ptr<SubsystemBase>(this, [](SubsystemBase*) {}));
}

std::set<std::shared_ptr<fridolinsRobotik::CommandBase>> SubsystemBase::getDefaultCommands()
{
    return defaultCommands;
}

void SubsystemBase::removeDefaultCommand(std::shared_ptr<fridolinsRobotik::CommandBase> command)
{
    defaultCommands.erase(command);
}

void SubsystemBase::addDefaultCommand(std::shared_ptr<fridolinsRobotik::CommandBase> command)
{
       defaultCommands.insert(command);
}



