cmake_minimum_required(VERSION 3.7)
project(IceHello)

set(CMAKE_C_STANDARD 99)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

find_package(Ice 3.4.0 REQUIRED Ice IceUtil Glacier2)
include_directories (${Ice_INCLUDE_DIRS})

find_file(config ice.config)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ice.config
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


set(CLIENT_FILES Client.cpp servants/User.h servants/User.cpp chat.cpp chat.h)
add_executable(client ${CLIENT_FILES})
target_link_libraries (client ${Ice_LIBRARIES} pthread)

set(GROUP_SERVER_MANAGER_FILES servants/GroupServer.cpp servants/GroupServer.h GroupServerManager.cpp servants/GroupServerManager.h servants/GroupServerManager.cpp chat.cpp chat.h)
add_executable(group_server_manager ${GROUP_SERVER_MANAGER_FILES})
target_link_libraries (group_server_manager ${Ice_LIBRARIES} pthread)

set(CHAT_SERVER_FILES ChatServer.cpp chat.cpp chat.h servants/ChatServer.h servants/ChatServer.cpp)
add_executable(chat_server ${CHAT_SERVER_FILES})
target_link_libraries (chat_server ${Ice_LIBRARIES} pthread)