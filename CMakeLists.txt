cmake_minimum_required(VERSION 3.20)

project(cpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_test
        main.cpp
        src/chat.cpp
        src/chat_message.cpp
        src/message_types.cpp
        src/user.cpp
        src/user_friends.cpp
        src/repos/user_repo.cpp
        src/repos/chat_repo.cpp
        src/repos/message_repo.cpp
        src/services/user_service.cpp
        src/services/chat_service.cpp
        src/services/message_service.cpp
        hello_handler.hpp
        include/cpp_test/services/user_service.h
        include/cpp_test/services/chat_service.h
        include/cpp_test/services/message_service.h
        include/cpp_test/repos/user_repo.h
        include/cpp_test/repos/chat_repo.h
        include/cpp_test/repos/message_repo.h
        include/cpp_test/user_friends.h
)

target_include_directories(cpp_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
