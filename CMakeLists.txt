cmake_minimum_required(VERSION 3.17)
project(Odin)

set(CMAKE_CXX_STANDARD 14)

include_directories(Odin/engine)
include_directories(Odin/uci)

#AddBOOST
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Boost 1.75.0 REQUIRED serialization)
#ENDBOOST

message(STATUS "---------------------")
message(STATUS "Boost_FOUND: ${Boost_FOUND}")
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "---------------------")

add_executable(Odin
        Odin/engine/Odin.cpp
        Odin/engine/Odin.h
        Odin/uci/uci.hpp
        Odin/main.cpp)
target_link_libraries(Odin PRIVATE Boost::serialization)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
