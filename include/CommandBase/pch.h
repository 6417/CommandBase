#ifndef COMMANDBASE_PCH_H
#define COMMANDBASE_PCH_H

#ifdef USE_STL
#include <set>
using std::set;
#else
#include "utilities/set.h"
#endif

#define RunningCommandsAllocator std::allocator<CommandBase*>

#endif //COMMANDBASE_PCH_H
