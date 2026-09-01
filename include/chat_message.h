#ifndef CPP_TEST_CHAT_MESSAGE_H
#define CPP_TEST_CHAT_MESSAGE_H

#include <ctime>

#include "../src/lib/types/message_types.h"

#include <string>

class ChatMessage
{
    std::string id;
    std::string msg;
    MessageType type;

    std::time_t createdAt;
    std::time_t updatedAt;

public:
    ChatMessage()
    {
        createdAt = std::time(nullptr);
        updatedAt = createdAt;
    } // TODO: Generate UUID

    void setMsg(const std::string& msg)
    {
        if (msg.empty()) return;
        this->msg = msg;
    }

    void setType(const MessageType type) { this->type = type; }

    const std::string& getMsg() const { return this->msg; }
    std::string& getMsg() { return this->msg; }

    MessageType getType() const { return this->type; }

    std::time_t getCreatedAt() const { return this->createdAt; }
    std::time_t getUpdatedAt() const { return this->updatedAt; }
};

#endif //CPP_TEST_CHAT_MESSAGE_H
