cmake_minimum_required(VERSION 3.17)
project(CommandBase)

set(CMAKE_CXX_STANDARD 11)

include_directories(src include)

set(SRC src/CommandBase/CommandBase.cpp src/CommandBase/CommandScheduler.cpp src/utilities/set.cpp src/utilities/LinkedList.cpp)

set(HEAD include/CommandBase/CommandBase.h include/SubsystemBase/pch.h include/CommandBase/CommandScheduler.h include/utilities/set.h include/utilities/LinkedList.h)

# add_compile_definitions(USE_STL)
add_library(${PROJECT_NAME} STATIC ${HEAD} ${SRC})

target_precompile_headers(${PROJECT_NAME} PUBLIC include/CommandBase/pch.h include/SubsystemBase/pch.h)

set(TEST_SRC test/main.cpp test/CommandBaseTest.cpp test/utilities/setTest.cpp)

set(TEST_HEAD test/pch.h test/CommandBaseTest.h test/utilities/setTest.h)

set(TEST_LIB ${PROJECT_NAME} /home/lib/googletest/build/lib/libgtest.so)

add_executable(TEST_${PROJECT_NAME} ${TEST_SRC} ${TEST_HEAD})

target_include_directories(TEST_${PROJECT_NAME} PRIVATE
		/home/lib/googletest/googletest/include
		./
		)
target_link_libraries(TEST_${PROJECT_NAME} ${TEST_LIB})

target_precompile_headers(TEST_${PROJECT_NAME} PRIVATE test/pch.h)

