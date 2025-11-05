cmake_minimum_required(VERSION 3.10)

project(logger_system_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES logger.cpp 
    test_logger.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(logger_demo ${SOURCES})

target_link_libraries(logger_demo pthread)
