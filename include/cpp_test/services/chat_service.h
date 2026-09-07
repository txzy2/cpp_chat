#ifndef CPP_TEST_CHAT_SERVICE_H
#define CPP_TEST_CHAT_SERVICE_H

#include "../repos/chat_repo.h"
#include "../repos/user_repo.h"
#include "cpp_test/chat.h"

class ChatService
{
    ChatRepo* chatRepo_;
    UserRepo* userRepo_;

public:
    explicit ChatService(ChatRepo* chatRepo, UserRepo* userRepo)
        : chatRepo_(chatRepo), userRepo_(userRepo) {}

    Chat createChat(const std::string& name);
    void addUserToChat(Chat& chat, const User& user);
    void removeUserFromChat(Chat& chat, uint64_t userId);
    void updateChatType(Chat& chat);
    ChatMessage* getLastMessage(Chat& chat);

    void saveChat(const Chat& chat);
    std::vector<Chat> getAllChats();

private:
    static void updateType(Chat& chat);
};

#endif // CPP_TEST_CHAT_SERVICE_H
