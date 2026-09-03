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

    const auto chatType = (type_ == INDIVIDUAL) ? "Individual" : "Group";
    const auto lastMsgTime = DateTimeHelper::formatTime(lastMsg->getCreatedAt());
    const auto lastMsgUpdateTime = DateTimeHelper::formatTime(lastMsg->getUpdatedAt());

    std::cout << std::format(
        "\nID: {}\n"
        "CHAT NAME: {} (TYPE: {})\n\n  TEXT: {} (ID: {})\n  From: {} (Type: {})\n\n  CREATED_AT: {}\n  UPDATED_AT: {}\n",
        boost::uuids::to_string(id_),
        name_,
        chatType,
        lastMsg->getMsg(),
        boost::uuids::to_string(lastMsg->getId()),
        lastMsg->getUser().getName(),
        enumToString(lastMsg->getType()),
        lastMsgTime,
        lastMsgUpdateTime
    );

    std::cout << "\nUSERS:\n";
    for (const auto& user : users_)
    {
        const auto status = (user.getStatus() == ACTIVE) ? "Active" : "Inactive";

        std::cout << std::format(
            "EXT_ID: {} NAME: {} ({})\n",
            boost::uuids::to_string(user.getExtId()),
            user.getName(),
            status
        );
    }
}
