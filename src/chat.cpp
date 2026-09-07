#include "../include/cpp_test/chat.h"
#include "../include/cpp_test/date_time_helper.h"

#include <format>
#include <iostream>

bool Chat::isUserInChat(const uint64_t userId) const
{
    for (const auto& u : users_)
    {
        if (u.getId() == userId) return true;
    }
    return false;
}

const ChatMessage* Chat::getLastMsg() const
{
    if (messages_.empty()) return nullptr;
    return &messages_.back();
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
