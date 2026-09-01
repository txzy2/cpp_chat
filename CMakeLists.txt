cmake_minimum_required(VERSION 3.20)

project(cpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third_party/userver)

add_executable(cpp_test
        main.cpp
        src/chat.cpp
        src/chat_message.cpp
        src/message_types.cpp
        src/user.cpp
        hello_handler.hpp
)

target_include_directories(cpp_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(cpp_test PRIVATE userver-core)