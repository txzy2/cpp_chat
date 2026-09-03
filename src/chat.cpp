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

    std::cout << std::format(
        "ID: {}\nCHAT NAME: {}\nLAST MSG ID: {}, TEXT: {} (From: {}, Type: {})\nCREATED_AT: {}\nUPDATED_AT: {}\n",
        boost::uuids::to_string(id_),
        name_,
        boost::uuids::to_string(lastMsg->getId()),
        lastMsg->getMsg(),
        lastMsg->getUser().getName(),
        enumToString(lastMsg->getType()),
        DateTimeHelper::formatTime(lastMsg->getCreatedAt()),
        DateTimeHelper::formatTime(lastMsg->getUpdatedAt())
    );

    std::cout << "\nUSERS:\n";
    for (const auto & user : users_)
    {
        std::cout << "EXT_ID: " << user.getExtId() << " NAME: " << user.getName()
            << " (" << (user.getStatus() == Status::ACTIVE ? "Active" : "Inactive") << ")\n";
    }
    std::cout << "\n";
}
