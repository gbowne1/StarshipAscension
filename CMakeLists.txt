cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "g++")
project(StarshipAscension VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

add_executable(StarshipAscension src/main.cpp src/game.cpp src/util.cpp)

# Link glog if installed
find_library(GLOG_LIBRARY glog)
if(GLOG_LIBRARY)
  target_link_libraries(StarshipAscension ${GLOG_LIBRARY})
endif()
