#include "CommandBase/CommandGroupBase.h"

fridolinsRobotik::CommandGroupBase::CommandGroupBase()
{
    commandsList = std::vector<CommandBase*>();
    currentCommandIndex = -1;
}
