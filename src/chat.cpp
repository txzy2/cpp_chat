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

    if (std::ranges::find_if(users_, [&user](const User& u)
    {
        return u.getId() == user.getId() || u.getStatus() == ACTIVE;
    }) == users_.end())
    {
        throw std::logic_error("User not found in chat");
    }

    if (messages_.size() >= MAX_MESSAGES) { messages_.pop_front(); }

    ChatMessage msgObj(type, user);
    msgObj.setMsg(msg);
    messages_.push_back(std::move(msgObj));
}

void Chat::getInfo() const
{
    const auto lastMsg = getLastMsg();
    if (!lastMsg)
    {
        throw std::logic_error("No last message");
    }

    std::cout << std::format(
        "\n=== CHAT ({}): {} (ID: {}) ===\n\n",
        (type_ == INDIVIDUAL) ? "Individual" : "Group",
        name_,
        boost::uuids::to_string(id_)
    );

    if (const std::optional<User> to = getReceiverUser(); to.has_value())
    {
        std::cout << std::format(
            " - TEXT: {} (ID: {})\n - From: {} (Name: {})\n - To: {} (Name: {})\n\n - CREATED_AT: {}\n - UPDATED_AT: {}\n",
            lastMsg->getMsg(),
            boost::uuids::to_string(lastMsg->getId()),
            lastMsg->getUser().getName(),
            boost::uuids::to_string(to->getExtId()),
            to->getName(),
            enumToString(lastMsg->getType()),
            DateTimeHelper::formatTime(lastMsg->getCreatedAt()),
            DateTimeHelper::formatTime(lastMsg->getUpdatedAt())
        );

        return;
    }

    throw std::logic_error("No user in chat");
}
