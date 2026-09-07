#ifndef CPP_TEST_MESSAGE_REPO_H
#define CPP_TEST_MESSAGE_REPO_H

#include <string>
#include <vector>

#include "cpp_test/chat_message.h"

class MessageRepo
{
    std::string filename_;

public:
    explicit MessageRepo(std::string filename) : filename_(std::move(filename)) {}

    void save(const ChatMessage& msg, const std::string& chatId) const;
    std::vector<ChatMessage> loadByChatId(const std::string& chatId) const;

private:
    static std::string messageToString(const ChatMessage& msg, const std::string& chatId);
    static ChatMessage stringToMessage(const std::string& str);
};

#endif // CPP_TEST_MESSAGE_REPO_H
