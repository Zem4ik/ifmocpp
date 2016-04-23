cmake_minimum_required(VERSION 3.4)
project(CProjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES Test.cpp)
add_executable(CProjects ${SOURCE_FILES})


install(TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)
