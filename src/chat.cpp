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

    auto it = users_.begin();
    for (; it != users_.end(); ++it)
    {
        if (it->getId() == user.getId() && it->getStatus() == Status::ACTIVE)
        {
            break;
        }
    }

    if (it == users_.end())
    {
        throw std::logic_error("User not found in chat");
    }

    if (messages_.size() >= MAX_MESSAGES) { messages_.pop_front(); }

    ChatMessage msgObj(type, user);
    msgObj.setMsg(msg);
    messages_.push_back(std::move(msgObj));
}

auto Chat::getReceiverUser() const -> std::optional<User>
{
    const auto* lastMsg = getLastMsg();

    if (!lastMsg) { return std::nullopt; }
    if (users_.size() != 2) { return std::nullopt; }

    for (const auto& user : users_) {
        if (user.getId() != lastMsg->getUser().getId() && user.getStatus() == Status::ACTIVE) {
            return user;
        }
    }

    return std::nullopt;
}

void Chat::addUser(const User& user) {
    for (const auto& u : users_) {
        if (u.getId() == user.getId()) { return; }
    }

    users_.push_back(user);
    updateType();
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
        (type_ == ChatType::INDIVIDUAL) ? "Individual" : "Group",
        name_,
        boost::uuids::to_string(id_)
    );

    std::cout << std::format(
        " - TEXT: {} (ID: {})\n - From: {} (ID: {})\n\n - CREATED_AT: {}\n - UPDATED_AT: {}\n\n",
        lastMsg->getMsg(),
        boost::uuids::to_string(lastMsg->getId()),
        lastMsg->getUser().getName(),
        boost::uuids::to_string(lastMsg->getUser().getExtId()),
        DateTimeHelper::formatTime(lastMsg->getCreatedAt()),
        DateTimeHelper::formatTime(lastMsg->getUpdatedAt())
    );

    std::cout << "CHAT USERS:\n";
    for (const auto& user : users_)
    {
        std::cout << std::format("ID: {}, NAME: {}\n", boost::uuids::to_string(user.getExtId()), user.getName());
    }
}
