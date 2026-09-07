#include "../../include/cpp_test/repos/message_repo.h"

#include <fstream>
#include <sstream>

#include "cpp_test/date_time_helper.h"
#include "cpp_test/message_types.h"

void MessageRepo::save(const ChatMessage& msg, const std::string& chatId) const
{
    std::ofstream file(filename_, std::ios::app);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename_);
    }

    file << messageToString(msg, chatId) << "\n";
}

auto MessageRepo::loadByChatId(const std::string& chatId) const -> std::vector<ChatMessage>
{
    std::vector<ChatMessage> messages;
    std::ifstream file(filename_);
    if (!file.is_open())
    {
        return messages;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string storedChatId;
        std::getline(iss, storedChatId, '|');

        if (storedChatId == chatId)
        {
            std::string rest;
            std::getline(iss, rest);
            messages.push_back(stringToMessage(rest));
        }
    }

    return messages;
}

std::string MessageRepo::messageToString(const ChatMessage& msg, const std::string& chatId)
{
    std::ostringstream oss;
    oss << chatId << "|"
        << boost::uuids::to_string(msg.getId()) << "|"
        << enumToString(msg.getType()) << "|"
        << msg.getMsg() << "|"
        << boost::uuids::to_string(msg.getUser().getExtId()) << "|"
        << DateTimeHelper::formatTime(msg.getCreatedAt()) << "|"
        << DateTimeHelper::formatTime(msg.getUpdatedAt());
    return oss.str();
}

ChatMessage MessageRepo::stringToMessage(const std::string& str)
{
    std::istringstream iss(str);
    std::string msgId, typeStr, msgText, userId, createdAt, updatedAt;

    std::getline(iss, msgId, '|');
    std::getline(iss, typeStr, '|');
    std::getline(iss, msgText, '|');
    std::getline(iss, userId, '|');
    std::getline(iss, createdAt, '|');
    std::getline(iss, updatedAt, '|');

    MessageType type = messageTypeToEnum(typeStr);
    User sender;
    sender.setName("");

    ChatMessage msg(type, sender);
    msg.setMsg(msgText);
    return msg;
}
