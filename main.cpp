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

    try {
        Chat c("Chat1");
        c.addUser(u1);
        c.addUser(u2);
        c.addMessage("MSG", STRING, u1);
        c.getInfo();
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
