//
// Created by kamaev on 9/1/26.
//

#include "../include/chat.h"
#include "lib/types/message_types.h"

#include <iostream>

void Chat::addMessage(const std::string& msg, MessageType type)
{
    if (users.empty() && users.size() < 2) { throw std::logic_error("No users found"); }
    if (messages.size() >= MAX_MESSAGES) { messages.pop_front(); }

    ChatMessage msgObj;
    msgObj.setMsg(msg);
    msgObj.setType(type);
    messages.push_back(std::move(msgObj));
}

void Chat::getInfo() const
{
    const auto lastMsg = getLastMsg();

    std::printf("ID: %lu\nCHAT NAME: %s\nLAST MSG: %s (Type: %s)\n",
                id,
                name.c_str(),
                lastMsg ? lastMsg->getMsg().c_str() : "Empty",
                lastMsg ? enumToString(lastMsg->getType()).c_str() : "UNKNOWN");

    std::printf("\nUSERS:\n");
    for (size_t i = 0; i < users.size(); ++i)
    {
        std::printf("%s (%s)", users[i].getName().c_str(),
                    users[i].getStatus() == Status::ACTIVE ? "Active" : "Inactive");

        if (i != users.size() - 1)
        {
            std::printf(", ");
        }
    }
}
