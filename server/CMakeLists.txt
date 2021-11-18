cmake_minimum_required(VERSION 3.20)

project(server)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB sources src/*.cpp)

add_library(server STATIC ${sources})
target_include_directories(server PUBLIC include)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES})
