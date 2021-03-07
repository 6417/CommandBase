cmake_minimum_required(VERSION 3.10)
project(CommandBase)

set(CMAKE_CXX_STANDARD 17)

include_directories(./src ./include)

set(BUILD_SHARED_LIBS )
set(SRC src/CommandBase/library.cpp)

set(HEAD include/CommandBase/library.h)

add_library(${PROJECT_NAME} ${HEAD} ${SRC})

set(TEST_SRC test/main.cpp)

set(TEST_HEAD)

set(TEST_LIB ${PROJECT_NAME} /usr/local/lib/googletest/build/lib/libgtest.so)

add_executable(TEST_${PROJECT_NAME} ${TEST_SRC} ${TEST_HEAD})

target_link_libraries(TEST_${PROJECT_NAME} ${TEST_LIB})

target_include_directories(TEST_${PROJECT_NAME} PRIVATE
		/usr/local/lib/googletest/googletest/include
)