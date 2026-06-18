cmake_minimum_required(VERSION 3.28)
project(client_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
