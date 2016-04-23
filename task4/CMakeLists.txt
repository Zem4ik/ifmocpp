cmake_minimum_required(VERSION 3.4)
project(CProjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES Test.cpp format.cpp)
add_executable(CProjects ${SOURCE_FILES})
add_library(format format.cpp)
target_link_libraries(CProjects format)

set(HEADERS Test.cpp)
set(SOURCES format.cpp)
install(TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)
