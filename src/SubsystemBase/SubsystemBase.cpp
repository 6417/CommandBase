#include "SubsystemBase/SubsystemBase.h"

void fridolinsRobotik::SubsystemBase::periodic()
{

}

fridolinsRobotik::SubsystemBase::~SubsystemBase()
{
    fridolinsRobotik::CommandScheduler::getInstance().unregisterSubsystem(this);
}


