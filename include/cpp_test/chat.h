#ifndef CPP_TEST_CHAT_H
#define CPP_TEST_CHAT_H

#include <deque>
#include <string>
#include <utility>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "chat_message.h"
#include "user.h"

class Chat {
public:
    enum class ChatType {
        INDIVIDUAL = 0,
        GROUP
    };

private:
    boost::uuids::uuid id_;
    std::string name_;
    ChatType type_;
    std::deque<ChatMessage> messages_;
    std::deque<User> users_;

public:
    static constexpr size_t MAX_MESSAGES = 100;

    explicit Chat(std::string name) : name_(std::move(name)), type_(ChatType::INDIVIDUAL) {
        id_ = boost::uuids::random_generator()();
    }

    void pushMessage(ChatMessage msg) { messages_.push_back(std::move(msg)); }
    void pushUser(const User& user) { users_.push_back(user); }

    void setType(ChatType type) { type_ = type; }
    void popFrontMessage() { if (!messages_.empty()) messages_.pop_front(); }

    [[nodiscard]] boost::uuids::uuid getId() const { return id_; }
    [[nodiscard]] const std::string& getName() const { return name_; }
    [[nodiscard]] ChatType getType() const { return type_; }
    [[nodiscard]] const std::deque<ChatMessage>& getMessages() const { return messages_; }
    [[nodiscard]] const std::deque<User>& getUsers() const { return users_; }

    [[nodiscard]] bool isUserInChat(uint64_t userId) const;
    [[nodiscard]] const ChatMessage* getLastMsg() const;

    void getInfo() const;
};

#endif //CPP_TEST_CHAT_H
