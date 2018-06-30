cmake_minimum_required(VERSION 3.10)
project(treet)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIR})

include_directories(.)

add_executable(treet
        depengine/Action.hpp
        depengine/Depengine.hpp
        depengine/DepException.hpp
        depengine/FileInfo.cpp
        depengine/FileInfo.hpp
        depengine/Registry.cpp
        depengine/Registry.hpp
        depengine/Rule.cpp
        depengine/Rule.hpp
        depengine/RuleDetails.cpp
        depengine/RuleDetails.hpp
        depengine/RulePattern.cpp
        depengine/RulePattern.hpp
        depengine/Var.hpp
        treet/build.hpp
        treet/ShellAction.cpp
        treet/ShellAction.hpp
        treet/treet.cpp)

target_link_libraries(treet ${Boost_LIBRARIES})
