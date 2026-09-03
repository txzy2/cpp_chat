#ifndef CPP_TEST_CHAT_H
#define CPP_TEST_CHAT_H

#include <cstdint>      // ← Добавить!
#include <deque>
#include <string>
#include <utility>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "chat_message.h"
#include "user.h"

class Chat {
    boost::uuids::uuid id_;
    std::string name_;
    std::deque<ChatMessage> messages_;
    std::deque<User> users_;

    static constexpr size_t MAX_MESSAGES = 100;

public:
    explicit Chat(std::string name) : name_(std::move(name)) {
        id_ = boost::uuids::random_generator()();
    }

    void addMessage(const std::string& msg, MessageType type, const User& user);
    void addUser(const User& user) { users_.push_back(user); }

    [[nodiscard]] const ChatMessage* getLastMsg() const {
        if (messages_.empty()) {
            return nullptr;
        }
        return &messages_.back();
    }

    [[nodiscard]] const std::deque<ChatMessage>& getMessages() const { return messages_; }
    [[nodiscard]] const std::deque<User>& getUsers() const { return users_; }

    [[nodiscard]] boost::uuids::uuid getId() const { return id_; }
    [[nodiscard]] const std::string& getName() const { return name_; }

    void getInfo() const;
};

#endif //CPP_TEST_CHAT_H