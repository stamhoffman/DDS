#Cmake file for build project stm32f103rbt6

cmake_minimum_required(VERSION 2.4)

project(stm32f103rbt6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(CLIENT_TARGET client)

set(CLIENT_SOURCES src/client/client.cpp)

add_executable(${CLIENT_TARGET} ${CLIENT_SOURCES})
