#include <iostream>
#include <vector>

#include "include/cpp_test/chat.h"
#include "include/cpp_test/user.h"

// #include <userver/clients/dns/component.hpp>
// #include <userver/components/minimal_server_component_list.hpp>
// #include <userver/server/handlers/tests_control.hpp>
// #include <userver/utils/daemon_run.hpp>

#include <array>
#include <memory>

#include "hello_handler.hpp"

constexpr std::array<std::string, 3> names = {"Anton", "Dima", "Masha"};
constexpr std::array<std::string, 3> emails = {"anton@anton.ru", "dima@dima.ru", "masha@masha.ru"};

static void generateUser(User &u, const int index)
{
    u.setName(names[index]);
    u.setEmail(emails[index]);
    u.setUsername(names[index]);
}

int main(int argc, char *argv[]) {
    std::array<std::unique_ptr<User>, names.size()> users;

    for (int i = 0; i < names.size(); ++i)
    {
        users[i] = std::make_unique<User>();
        generateUser(*users[i], i);
    }

    try {
        std::vector<Chat> chats;
        Chat c("Chat1"), c2("Chat2");

        c.addUser(*users[0]);
        c.addUser(*users[2]);
        c.addMessage("Привет, как дела?", STRING, *users[0]);

        c2.addUser(*users[1]);
        c2.addUser(*users[0]);
        c2.addMessage("Димка, в майн пойдешь?", STRING, *users[0]);

        chats.push_back(c);
        chats.push_back(c2);

        for (auto& chat : chats)
        {
            chat.getInfo();
        }
    } catch (std::exception &e) {
        std::cerr << e.what();
    }
    //
    // auto component_list = userver::components::MinimalServerComponentList()
    //                               .Append<userver::clients::dns::Component>()
    //                               .Append<HelloHandler>();
    //
    // return userver::utils::DaemonMain(argc, argv, component_list);

    return 0;
}
