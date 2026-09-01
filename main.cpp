#include <iostream>
#include <vector>

#include "include/chat.h"

int main()
{
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

    try
    {
        Chat c("Chat1");
        c.addUser(u1);
        c.addUser(u2);
        c.addMessage("MSG", MessageType::STRING, u1);
        c.getInfo();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }

    return 0;
}
