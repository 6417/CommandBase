#include "CommandBase/CommandBase.h"

void fridolinsRobotik::CommandBase::initialize()
{

}

void fridolinsRobotik::CommandBase::execute()
{

}

void fridolinsRobotik::CommandBase::end(bool interrupted)
{

}

bool fridolinsRobotik::CommandBase::isFinished()
{
    return true;
}


std::set<std::shared_ptr<fridolinsRobotik::SubsystemBase>> fridolinsRobotik::CommandBase::getRequirements()
{
    return requirements;
}

void fridolinsRobotik::CommandBase::addRequirements(std::shared_ptr<SubsystemBase> subsystem)
{
    requirements.insert(subsystem);
}

void fridolinsRobotik::CommandBase::addRequirements(std::set<std::shared_ptr<SubsystemBase>> subsystems)
{
    requirements.insert(subsystems.begin(), subsystems.end());
}

bool fridolinsRobotik::CommandBase::hasRequirements()
{
    return requirements.empty();
}

// for ~CommandBase() see CommandScheduler.cpp