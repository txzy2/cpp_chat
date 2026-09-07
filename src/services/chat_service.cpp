#include "../../include/cpp_test/services/chat_service.h"

Chat ChatService::createChat(const std::string& name)
{
    return Chat(name);
}

void ChatService::addUserToChat(Chat& chat, const User& user)
{
    if (chat.isUserInChat(user.getId()))
    {
        throw std::logic_error("User already in chat");
    }

    chat.pushUser(user);
    updateType(chat);
}

void ChatService::removeUserFromChat(Chat& chat, uint64_t userId)
{
    // TODO: implement remove if needed
    (void)chat;
    (void)userId;
}

void ChatService::updateChatType(Chat& chat)
{
    updateType(chat);
}

ChatMessage* ChatService::getLastMessage(Chat& chat)
{
    // returns mutable pointer for service use
    return const_cast<ChatMessage*>(chat.getLastMsg());
}

void ChatService::saveChat(const Chat& chat)
{
    chatRepo_->save(chat);
}

std::vector<Chat> ChatService::getAllChats()
{
    return chatRepo_->loadAll();
}

void ChatService::updateType(Chat& chat)
{
    auto type = (chat.getUsers().size() > 2)
        ? Chat::ChatType::GROUP
        : Chat::ChatType::INDIVIDUAL;
    chat.setType(type);
}
