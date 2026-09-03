#ifndef CPP_TEST_CHAT_MESSAGE_H
#define CPP_TEST_CHAT_MESSAGE_H

#include <ctime>
#include <stdexcept>
#include <string>
#include <utility>

#include "message_types.h"
#include "user.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class ChatMessage
{
    boost::uuids::uuid id_;
    std::string msg_;
    MessageType type_;
    User user_;
    std::time_t createdAt_;
    std::time_t updatedAt_;

public:
    explicit ChatMessage(const MessageType type, User user) : type_(type), user_(std::move(user))
    {
        if (type_ == UNKNOWN)
        {
            throw std::logic_error("Unknown message type");
        }

        id_ = boost::uuids::random_generator()();
    }

    void setMsg(const std::string& msg)
    {
        if (msg.empty()) return;
        msg_ = msg;
        updatedAt_ = std::time(nullptr);
    }

    // Геттеры
    [[nodiscard]] boost::uuids::uuid getId() const { return id_; }
    [[nodiscard]] const std::string& getMsg() const { return msg_; }
    [[nodiscard]] MessageType getType() const { return type_; }
    [[nodiscard]] std::time_t getCreatedAt() const { return createdAt_; }
    [[nodiscard]] std::time_t getUpdatedAt() const { return updatedAt_; }
    [[nodiscard]] const User& getUser() const { return user_; }
};

#endif //CPP_TEST_CHAT_MESSAGE_H
