#ifndef TEST_PCH_H
#define TEST_PCH_H

#include <gtest/gtest.h>
#include "CommandBase/pch.h"
#include <memory>
namespace test
{
    template<typename T>
    std::shared_ptr<T> make_stack_pointer(T* ptr)
    {
        return std::shared_ptr<T>(ptr, [](T*)
        {});
    }
}

#endif //TEST_PCH_H
