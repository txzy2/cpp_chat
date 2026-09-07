#ifndef CPP_TEST_MESSAGE_SERVICE_H
#define CPP_TEST_MESSAGE_SERVICE_H

#include "../repos/message_repo.h"
#include "../repos/user_repo.h"
#include "cpp_test/chat.h"

class MessageService
{
    MessageRepo* messageRepo_;
    UserRepo* userRepo_;

public:
    explicit MessageService(MessageRepo* messageRepo, UserRepo* userRepo)
        : messageRepo_(messageRepo), userRepo_(userRepo) {}

    void sendMessage(Chat& chat, const std::string& msg, MessageType type, const User& user);
    std::vector<ChatMessage> getMessages(const std::string& chatId);

private:
    bool isUserInChat(const Chat& chat, uint64_t userId);
    bool isUserFriend(uint64_t userId, uint64_t friendId);
};

#endif // CPP_TEST_MESSAGE_SERVICE_H
