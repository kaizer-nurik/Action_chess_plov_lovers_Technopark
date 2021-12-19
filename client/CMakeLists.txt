cmake_minimum_required(VERSION 3.20)

project(client)

find_package(SFML REQUIRED COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS system json)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB sources src/*.cpp)

add_library(client STATIC ${sources})
target_include_directories(client PUBLIC include include/requests include/responses)
target_link_libraries(client PUBLIC -lsfml-graphics -lsfml-window -lsfml-system ${Boost_LIBRARIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)
target_link_libraries(main client -pthread)
