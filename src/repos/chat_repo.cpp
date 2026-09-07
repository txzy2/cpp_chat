#include "../../include/cpp_test/repos/chat_repo.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "cpp_test/date_time_helper.h"
#include "cpp_test/message_types.h"

void ChatRepo::save(const Chat& chat)
{
    std::ofstream file(filename_, std::ios::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename_);
    }

    file << chatToString(chat) << "\n";
}

std::vector<Chat> ChatRepo::loadAll()
{
    std::vector<Chat> chats;
    std::ifstream file(filename_);
    if (!file.is_open())
    {
        return chats;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            chats.push_back(stringToChat(line));
        }
    }

    return chats;
}

std::string ChatRepo::chatToString(const Chat& chat)
{
    std::ostringstream oss;
    oss << boost::uuids::to_string(chat.getId()) << "|"
        << chat.getName() << "|";

    const auto& users = chat.getUsers();
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (i > 0) oss << ",";
        oss << boost::uuids::to_string(users[i].getExtId()) << ":"
            << users[i].getName() << ":"
            << users[i].getEmail();
    }

    oss << "|";

    const auto& messages = chat.getMessages();
    for (size_t i = 0; i < messages.size(); ++i)
    {
        if (i > 0) oss << ";";
        oss << enumToString(messages[i].getType()) << ":"
            << messages[i].getMsg() << ":"
            << boost::uuids::to_string(messages[i].getUser().getExtId()) << ":"
            << DateTimeHelper::formatTime(messages[i].getCreatedAt());
    }

    return oss.str();
}

Chat ChatRepo::stringToChat(const std::string& str)
{
    std::istringstream iss(str);
    std::string token;

    std::getline(iss, token, '|');
    std::string chatId = token;

    std::getline(iss, token, '|');
    std::string chatName = token;

    Chat chat(chatName);

    std::getline(iss, token, '|');
    std::istringstream usersStream(token);
    std::string userToken;
    while (std::getline(usersStream, userToken, ','))
    {
        if (userToken.empty()) continue;
        std::istringstream userIss(userToken);
        std::string extId, name, email;
        std::getline(userIss, extId, ':');
        std::getline(userIss, name, ':');
        std::getline(userIss, email, ':');

        User u;
        u.setName(name);
        u.setEmail(email);
        chat.pushUser(u);
    }

    std::getline(iss, token, '|');
    std::istringstream msgStream(token);
    std::string msgToken;
    while (std::getline(msgStream, msgToken, ';'))
    {
        if (msgToken.empty()) continue;
        std::istringstream msgIss(msgToken);
        std::string typeStr, msgText, userId, createdAt;
        std::getline(msgIss, typeStr, ':');
        std::getline(msgIss, msgText, ':');
        std::getline(msgIss, userId, ':');
        std::getline(msgIss, createdAt, ':');

        MessageType type = messageTypeToEnum(typeStr);
        User sender;
        sender.setName("");

        ChatMessage msgObj(type, sender);
        msgObj.setMsg(msgText);
        chat.pushMessage(std::move(msgObj));
    }

    return chat;
}
