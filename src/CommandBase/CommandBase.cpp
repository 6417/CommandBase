#include "CommandBase/CommandBase.h"
#include "CommandBase/CommandScheduler.h"

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

fridolinsRobotik::CommandBase::~CommandBase()
{
    fridolinsRobotik::CommandScheduler::getInstance().cancel(std::shared_ptr<CommandBase>(this, [](CommandBase*) {}));
}