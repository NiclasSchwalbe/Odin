cmake_minimum_required(VERSION 3.17)
project(Odin)

set(CMAKE_CXX_STANDARD 14)

include_directories(Odin/engine)
include_directories(Odin/uci)
include_directories(Odin/util)

# add our cmake modules under cmake/
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#AddBOOST
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

if(WIN32)
SET(BOOST_ROOT "C:/Program Files (x86)/boost/boost_1_75_0/")
endif (WIN32)

find_package(Boost 1.75.0 REQUIRED serialization)

#ENDBOOST

message(STATUS "---------------------")
message(STATUS "Boost_FOUND: ${Boost_FOUND}")
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "---------------------")

# Include CPM dependency manager
include(CPM)

# enable testing
enable_testing()

# Pull doctest using CPM
cpmaddpackage("gh:onqtam/doctest#2.4.5")

# add the CMake modules for automatic test discovery so we can use
# doctest_discover_tests() CMake
set(CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/scripts/cmake"
        ${CMAKE_MODULE_PATH})

add_executable(Odin
        Odin/engine/Odin.cc
        Odin/main.cc
        Odin/engine/Board.cc
        Odin/engine/Figure.cc
        Odin/util/Utility.cc
        Odin/engine/Node.cc
        Odin/engine/Link.cc
        Odin/engine/Odin.h
        Odin/engine/Board.h
        Odin/engine/Figure.h
        Odin/util/Utility.h
        Odin/engine/Node.h
        Odin/engine/Link.h
        )

target_link_libraries(Odin PRIVATE Boost::serialization)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

