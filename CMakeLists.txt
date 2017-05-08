cmake_minimum_required(VERSION 3.7)
project(IceHello)

set(CMAKE_C_STANDARD 99)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

find_package(Ice 3.4.0 REQUIRED Ice IceUtil Glacier2)
include_directories (${Ice_INCLUDE_DIRS})

set(SERVER_FILES servants/GroupServer.h servants/GroupServer.cpp servants/GroupServerManager.h servants/GroupServerManager.cpp servants/User.h chat.cpp chat.h main.cpp servants/User.cpp servants/ChatServer.h servants/ChatServer.cpp)
add_executable(server ${SERVER_FILES})

target_link_libraries (server ${Ice_LIBRARIES} pthread)