#ifndef CPP_TEST_CHAT_MESSAGE_H
#define CPP_TEST_CHAT_MESSAGE_H

#include "../src/lib/types/message_types.h"

#include <string>

class ChatMessage
{
    std::string id;
    std::string msg;
    MessageType type;

public:
    ChatMessage()
    {
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
};

#endif //CPP_TEST_CHAT_MESSAGE_H
