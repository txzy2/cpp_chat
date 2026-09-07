#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "include/cpp_test/chat.h"
#include "include/cpp_test/user.h"
#include "include/cpp_test/repos/user_repo.h"
#include "include/cpp_test/repos/chat_repo.h"
#include "include/cpp_test/repos/message_repo.h"
#include "include/cpp_test/services/user_service.h"
#include "include/cpp_test/services/chat_service.h"
#include "include/cpp_test/services/message_service.h"

namespace {

    const std::array<std::string, 3> names = {"Anton", "Dima", "Masha"};
    const std::array<std::string, 3> emails = {"anton@anton.ru", "dima@dima.ru", "masha@masha.ru"};

    void generateUser(User &u, const std::size_t index)
    {
        u.setName(names[index]);
        u.setEmail(emails[index]);
        u.setUsername(names[index]);
    }

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    std::array<User, names.size()> users;
    for (std::size_t i = 0; i < names.size(); ++i)
    {
        generateUser(users[i], i);
    }

    UserRepo userRepo("storage/user_friends.txt");
    ChatRepo chatRepo("storage/chats.txt");
    MessageRepo messageRepo("storage/messages.txt");

    UserService userService(&userRepo);
    ChatService chatService(&chatRepo, &userRepo);
    MessageService messageService(&messageRepo, &userRepo);

    try {
        userService.addFriend(users[0].getId(), users[1]);
        userService.addFriend(users[0].getId(), users[2]);
        userService.addFriend(users[1].getId(), users[0]);
        userService.addFriend(users[1].getId(), users[2]);

        std::cout << "Friends of " << users[0].getName() << ":\n";
        for (const auto& f : userService.getFriends(users[0].getId()))
        {
            std::cout << " - " << f.getName() << "\n";
        }

        Chat chat1 = chatService.createChat("Chat1");
        chatService.addUserToChat(chat1, users[0]);
        chatService.addUserToChat(chat1, users[1]);
        chatService.addUserToChat(chat1, users[2]);

        Chat chat2 = chatService.createChat("Chat2");
        chatService.addUserToChat(chat2, users[0]);
        chatService.addUserToChat(chat2, users[1]);

        messageService.sendMessage(chat1, "Привет, как дела?", MessageType::STRING, users[0]);
        messageService.sendMessage(chat2, "Димка, в майн пойдешь?", MessageType::STRING, users[0]);

        chat1.getInfo();
        chat2.getInfo();

        chatService.saveChat(chat1);
        chatService.saveChat(chat2);

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
