#ifndef CPP_TEST_CHAT_MESSAGE_H
#define CPP_TEST_CHAT_MESSAGE_H

#include <ctime>
#include <optional>
#include <stdexcept>
#include <string>

#include "../src/lib/types/message_types.h"
#include "user.h"

class ChatMessage
{
    std::string id_;
    std::string msg_;
    MessageType type_;
    User user_;
    std::time_t createdAt_;
    std::time_t updatedAt_;

public:
    explicit ChatMessage(const MessageType type, const User& user)
        : type_(type), user_(user)
    {
        if (type_ == UNKNOWN)
        {
            throw std::logic_error("Unknown message type");
        }

        if (user_.getId() == 0) {
            throw std::logic_error("Invalid user: ID is 0");
        }

        createdAt_ = std::time(nullptr);
        updatedAt_ = createdAt_;
    } // TODO: Generate UUID

    void setMsg(const std::string& msg)
    {
        if (msg.empty()) return;
        msg_ = msg;
        updatedAt_ = std::time(nullptr);
    }

    // Геттеры
    [[nodiscard]] const std::string& getMsg() const { return msg_; }
    [[nodiscard]] MessageType getType() const { return type_; }
    [[nodiscard]] std::time_t getCreatedAt() const { return createdAt_; }
    [[nodiscard]] std::time_t getUpdatedAt() const { return updatedAt_; }
    [[nodiscard]] const User& getUser() const { return user_; }
};

#endif //CPP_TEST_CHAT_MESSAGE_H