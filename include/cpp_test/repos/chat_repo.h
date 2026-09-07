#ifndef CPP_TEST_CHAT_REPO_H
#define CPP_TEST_CHAT_REPO_H

#include <string>
#include <vector>

#include "cpp_test/chat.h"

class ChatRepo
{
    std::string filename_;

public:
    explicit ChatRepo(std::string filename) : filename_(std::move(filename)) {}

    void save(const Chat& chat);
    std::vector<Chat> loadAll();

private:
    static std::string chatToString(const Chat& chat);
    static Chat stringToChat(const std::string& str);
};

#endif // CPP_TEST_CHAT_REPO_H
