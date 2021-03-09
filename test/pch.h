#ifndef TEST_PCH_H
#define TEST_PCH_H

#include <gtest/gtest.h>
#include "CommandBase/pch.h"

template<typename T>
class AllocTest : public std::allocator<T>
{
public:
    typename std::allocator_traits<std::allocator<T>>::pointer allocate(typename std::allocator_traits<std::allocator<T>>::size_type count)
    {
        std::cout << "allocated: " << count << std::endl;
        return std::allocator<T>::allocate(count);
    }

    void deallocate(typename std::allocator_traits<std::allocator<T>>::pointer p, typename std::allocator_traits<std::allocator<T>>::size_type count) {
        std::cout << "allocated: " << count << std::endl;
        std::allocator<T>::deallocate(p, count);
    }
};

#undef RunningCommandsAllocator
#define RunningCommandsAllocator AllocTest<fridolinsRobotik::CommandBase*>

#endif //TEST_PCH_H
