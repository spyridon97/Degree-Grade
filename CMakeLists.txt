cmake_minimum_required(VERSION 3.9)
project(Degree_Grade)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
set(CMAKE_EXE_LINKER_FLAGS -static)

set(Boost_INCLUDE_DIR c:/mingw/include/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES
        Source/Course.cpp
        Source/Semester.cpp
        Source/Student.cpp)

set(HEADER_FILES
        include/Course.hpp
        include/Semester.hpp
        include/Student.hpp)

include_directories(Source)
include_directories(include)

add_executable(DegreeGrade ${SOURCE_FILES} ${HEADER_FILES} main.cpp)