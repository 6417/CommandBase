cmake_minimum_required(VERSION 3.17)
project(CommandBase)

set(CMAKE_CXX_STANDARD 17)

include_directories(src include)

set(SRC src/CommandBase/CommandBase.cpp src/CommandBase/CommandScheduler.cpp)

set(HEAD include/CommandBase/CommandBase.h include/SubsystemBase/pch.h include/CommandBase/CommandScheduler.h)

add_library(${PROJECT_NAME} ${HEAD} ${SRC})

target_precompile_headers(${PROJECT_NAME} PUBLIC include/CommandBase/pch.h include/SubsystemBase/pch.h)

set(TEST_SRC test/main.cpp test/CommandBaseTest.h test/CommandBaseTest.cpp)

set(TEST_HEAD test/pch.h)

set(TEST_LIB ${PROJECT_NAME} /usr/local/lib/googletest/build/lib/libgtest.so)

add_executable(TEST_${PROJECT_NAME} ${TEST_SRC} ${TEST_HEAD})

target_include_directories(TEST_${PROJECT_NAME} PRIVATE
		/usr/local/lib/googletest/googletest/include
		)
target_link_libraries(TEST_${PROJECT_NAME} ${TEST_LIB})

target_precompile_headers(TEST_${PROJECT_NAME} PRIVATE test/pch.h)

