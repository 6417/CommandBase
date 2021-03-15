#include "CommandBase/CommandGroupBase.h"

fridolinsRobotik::CommandGroupBase::CommandGroupBase()
{
    commandsList = std::vector<std::shared_ptr<CommandBase>>();
}
