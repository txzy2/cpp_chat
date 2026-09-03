#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "include/cpp_test/chat.h"
#include "include/cpp_test/user.h"

// #include <userver/clients/dns/component.hpp>
// #include <userver/components/minimal_server_component_list.hpp>
// #include <userver/server/handlers/tests_control.hpp>
// #include <userver/utils/daemon_run.hpp>

#include "hello_handler.hpp"

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

    try {
        std::vector<Chat> chats;
        chats.reserve(2);
        chats.emplace_back("Chat1");
        chats.emplace_back("Chat2");

        chats[0].addUser(users[0]);
        chats[0].addUser(users[2]);
        chats[0].addMessage("Привет, как дела?", MessageType::STRING, users[0]);

        chats[1].addUser(users[1]);
        chats[1].addUser(users[0]);
        chats[1].addMessage("Димка, в майн пойдешь?", MessageType::STRING, users[0]);

        for (auto &chat : chats)
        {
            chat.getInfo();
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    // auto component_list = userver::components::MinimalServerComponentList()
    //                               .Append<userver::clients::dns::Component>()
    //                               .Append<HelloHandler>();
    //
    // return userver::utils::DaemonMain(argc, argv, component_list);

    return 0;
}