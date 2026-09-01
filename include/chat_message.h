#ifndef CPP_TEST_CHAT_MESSAGE_H
#define CPP_TEST_CHAT_MESSAGE_H

#include <ctime>
#include <optional>
#include <stdexcept>

#include "../src/lib/types/message_types.h"

#include <string>

#include "user.h"

class ChatMessage
{
    std::string id;
    std::string msg;
    MessageType type;

    User user_;

    std::time_t createdAt;
    std::time_t updatedAt;

public:
    explicit ChatMessage(const MessageType type, User user) : type(type), user_(user)
    {
        if (type == MessageType::UNKNOWN)
        {
            throw std::logic_error("Unknown message type");
        }

        createdAt = std::time(nullptr);
        updatedAt = createdAt;
    } // TODO: Generate UUID

    void setMsg(const std::string& msg)
    {
        if (msg.empty()) return;
        this->msg = msg;
    }

    [[nodiscard]] const std::string& getMsg() const { return this->msg; }
    [[nodiscard]] MessageType getType() const { return this->type; }
    [[nodiscard]] std::time_t getCreatedAt() const { return this->createdAt; }
    [[nodiscard]] std::time_t getUpdatedAt() const { return this->updatedAt; }
    [[nodiscard]] User getUser() const { return user_; }
};

#endif //CPP_TEST_CHAT_MESSAGE_H
