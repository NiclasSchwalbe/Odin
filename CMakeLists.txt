cmake_minimum_required(VERSION 3.17)
project(Odin)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

message("Parallelizing with ${N} Cores")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include_directories(Odin/engine)
include_directories(Odin/uci)
include_directories(Odin/util)
include_directories(Odin/util/iters)


# add our cmake modules under cmake/
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Include CPM dependency manager
include(CPM)

find_package(Boost 1.74.0 REQUIRED serialization)

message(STATUS "---------------------")
message(STATUS "Boost_FOUND: ${Boost_FOUND}")
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "---------------------")

#EndBoost
set(SRCS
        Odin/engine/Odin.cc
        Odin/engine/Board.cc
        Odin/util/Utility.cc
        Odin/engine/Node.cc
        Odin/engine/Link.cc
        Odin/engine/pawnlogic.cc
        Odin/engine/knightlogic.cc
        Odin/engine/longrangepiecelogic.cc
        Odin/engine/kinglogic.cc
        Odin/engine/Odin.h
        Odin/engine/Board.h
        Odin/engine/Figure.h
        Odin/util/Utility.h
        Odin/engine/Node.h
        Odin/engine/Link.h
        Odin/engine/movegenereration.cc)

add_executable(Odin Odin/main.cc)

add_library(Engine ${SRCS})
target_link_libraries(Odin PRIVATE Boost::serialization Engine)

if(UNIX)
set(CMAKE_CXX_FLAGS "-O3 -march=native")
endif(UNIX)

#Make Tests
#enable testing
enable_testing()

# Pull doctest using CPM
cpmaddpackage("gh:onqtam/doctest#2.4.5")

# add the CMake modules for automatic test discovery so we can use
# doctest_discover_tests() CMake
set(CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/scripts/cmake"
        ${CMAKE_MODULE_PATH})


add_subdirectory(Testing)
