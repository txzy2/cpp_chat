//
// Created by kamaev on 9/1/26.
//

#include "../include/cpp_test/chat.h"
#include "../include/cpp_test/message_types.h"
#include "../include/cpp_test/date_time_helper.h"

#include <format>
#include <iostream>

void Chat::addMessage(const std::string& msg, const MessageType type, const User& user)
{
    if (users_.empty())
    {
        throw std::logic_error("No users found");
    }

    if (const auto it = std::ranges::find_if(users_, [&user](const User& u)
    {
        return u.getId() == user.getId();
    }); it == users_.end())
    {
        throw std::logic_error("User not found in chat");
    }

    if (messages_.size() >= MAX_MESSAGES)
    {
        messages_.pop_front();
    }

    ChatMessage msgObj(type, user);
    msgObj.setMsg(msg);
    messages_.push_back(std::move(msgObj));
}

void Chat::getInfo() const
{
    const auto lastMsg = getLastMsg();
    if (!lastMsg) { throw std::logic_error("No last message"); }

    const std::string output = std::format(
        "ID: {}\nCHAT NAME: {}\nLAST MSG: {} (From: {}, Type: {})\nCREATED_AT: {}\nUPDATED_AT: {}\n",
        id_,
        name_,
        lastMsg->getMsg(),
        lastMsg->getUser().getName(),
        enumToString(lastMsg->getType()),
        DateTimeHelper::formatTime(lastMsg->getCreatedAt()),
        DateTimeHelper::formatTime(lastMsg->getUpdatedAt())
    );

    std::cout << output;

    std::cout << "\nUSERS:\n";
    for (size_t i = 0; i < users_.size(); ++i)
    {
        std::cout << "ID: " << users_[i].getId() << " NAME: " << users_[i].getName()
            << " (" << (users_[i].getStatus() == Status::ACTIVE ? "Active" : "Inactive") << ")";

        if (i != users_.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}
