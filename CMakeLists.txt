cmake_minimum_required(VERSION 3.15)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(source)

add_executable(Assignment1
        include/Action.h
        include/json.hpp
        include/Session.h
        include/User.h
        include/Watchable.h
        source/Main.cpp
        source/user.cpp
        source/Watchable.cpp)
