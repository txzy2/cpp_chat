#include <iostream>
#include <vector>

#include "include/cpp_test/chat.h"
#include "include/cpp_test/user.h"

// #include <userver/clients/dns/component.hpp>
// #include <userver/components/minimal_server_component_list.hpp>
// #include <userver/server/handlers/tests_control.hpp>
// #include <userver/utils/daemon_run.hpp>

#include "hello_handler.hpp"

int main(int argc, char *argv[]) {
    std::vector<User> users;
    std::vector<Chat> chats;

    User u1;
    u1.setName("Anton");
    u1.setEmail("anton@anton.ru");
    u1.setUsername("anton");

    users.push_back(u1);

    User u2;
    u2.setName("Masha");
    u2.setEmail("masha@masha.ru");
    u2.setUsername("masha");

    users.push_back(u2);

    User u3;
    u3.setName("Dima");
    u3.setEmail("dima@dima.ru");
    u3.setUsername("dima");

    users.push_back(u3);

    try {
        Chat c("Chat1");
        c.addUser(u1);
        c.addUser(u2);
        c.addMessage("Привет, как дела?", STRING, u1);
        chats.push_back(c);

        Chat c2("Chat2");
        c2.addUser(u3);
        c2.addUser(u1);
        c2.addMessage("Димка, в майн пойдешь?", STRING, u1);
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
