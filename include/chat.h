#ifndef CPP_TEST_CHAT_H
#define CPP_TEST_CHAT_H
#include <deque>
#include <string>

#include "chat_message.h"
#include "user.h"

class Chat
{
    u_int64_t id;
    std::string name;

    std::deque<ChatMessage> messages;
    std::deque<User> users;

    static constexpr size_t MAX_MESSAGES = 100;

public:
    explicit Chat(const std::string& name) : name(name)
    {
        this->id = messages.size() + 1;
    }

    void addMessage(const std::string& msg, MessageType type);
    void addUser(const User& user) { this->users.push_back(user); }

    const ChatMessage* getLastMsg() const
    {
        if (users.empty() && users.size() < 2) { throw std::logic_error("No users found"); }
        return messages.empty() ? nullptr : &messages.back();
    }

    std::deque<ChatMessage>& getMessages()
    {
        if (users.empty() && users.size() < 2) { throw std::logic_error("No users found"); }
        return messages;
    }

    std::deque<User>& getUsers()
    {
        if (users.empty() && users.size() < 2) { throw std::logic_error("No users found"); }
        return users;
    }

    u_int64_t getId() const { return this->id; }
    std::string getName() const { return this->name; }

    void getInfo() const;
};

#endif //CPP_TEST_CHAT_H
