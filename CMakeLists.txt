cmake_minimum_required(VERSION 4.3)
project(cpp_test)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(cpp_test
        main.cpp
        src/chat.cpp
        src/chat_message.cpp
        src/message_types.cpp
        src/user.cpp)
