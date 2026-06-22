cmake_minimum_required(VERSION 3.28)
project(client_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server
        src/server.cpp
        src/SocketUtils.cpp
        src/ClientHandler.cpp
)
add_executable(client src/client.cpp)

target_include_directories(server PRIVATE include)
target_include_directories(client PRIVATE include)