cmake_minimum_required(VERSION 4.3)
project(cpp_test)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_test main.cpp
        src/chat.cpp
        include/chat.h
        src/chat_message.cpp
        src/message_types.cpp
        include/chat_message.h
        src/lib/types/message_types.h
        src/user.cpp
        include/user.h)
