#include "CommandBase/CommandBase.h"

void fridolinsRobotik::CommandBase::initialize()
{
    initialized = true;
}

void fridolinsRobotik::CommandBase::execute()
{

}

void fridolinsRobotik::CommandBase::end(bool interrupted)
{
    initialized = false;
}

bool fridolinsRobotik::CommandBase::isFinished()
{
    return true;
}

bool fridolinsRobotik::CommandBase::hasBeenInitialized()
{
    return initialized;
}
