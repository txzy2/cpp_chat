//
// Created by kamaev on 9/1/26.
//

#include "../include/chat.h"

#include <format>

#include "lib/types/message_types.h"

#include <iostream>

#include "../include/date_time_helper.h"

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
    if (!lastMsg) { throw std::logic_error("No last message"); }

    const std::string output = std::format(
        "ID: {}\nCHAT NAME: {}\nLAST MSG: {} (Type: {})\nCREATED_AT: {}\nUPDATED_AT: {}\n",
        id,
        name,
        lastMsg->getMsg(),
        enumToString(lastMsg->getType()),
        DateTimeHelper::formatTime(lastMsg->getCreatedAt()),
        DateTimeHelper::formatTime(lastMsg->getUpdatedAt())
    );

    std::cout << output;

    std::cout << "\nUSERS:\n";
    for (size_t i = 0; i < users.size(); ++i)
    {
        std::cout << users[i].getName()
            << " (" << (users[i].getStatus() == Status::ACTIVE ? "Active" : "Inactive") << ")";

        if (i != users.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}
