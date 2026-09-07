#include "../../include/cpp_test/services/message_service.h"

void MessageService::sendMessage(Chat& chat, const std::string& msg, MessageType type, const User& user)
{
    if (!isUserInChat(chat, user.getId()))
    {
        throw std::logic_error("User not in chat");
    }

    if (type == MessageType::UNKNOWN)
    {
        throw std::logic_error("Unknown message type");
    }

    if (msg.empty())
    {
        throw std::logic_error("Message cannot be empty");
    }

    if (chat.getMessages().size() >= Chat::MAX_MESSAGES)
    {
        chat.popFrontMessage();
    }

    ChatMessage messageObj(type, user);
    messageObj.setMsg(msg);
    chat.pushMessage(std::move(messageObj));
}

std::vector<ChatMessage> MessageService::getMessages(const std::string& chatId)
{
    return messageRepo_->loadByChatId(chatId);
}

bool MessageService::isUserInChat(const Chat& chat, uint64_t userId)
{
    return chat.isUserInChat(userId);
}

bool MessageService::isUserFriend(uint64_t userId, uint64_t friendId)
{
    return userRepo_->areFriends(userId, friendId);
}
