#include "../include/cpp_test/message_types.h"

#include <cstring>
#include <string>

std::string enumToString(const MessageType type)
{
    switch (type)
    {
    case MessageType::PHOTO:
        return "photo";
    case MessageType::STRING:
        return "string";
    case MessageType::VIDEO:
        return "video";
    default:
        return "";
    }
};

MessageType messageTypeToEnum(const std::string& type)
{
    if (strcmp(type.c_str(), "photo") == 0) { return MessageType::PHOTO; }
    if (strcmp(type.c_str(), "string") == 0) { return MessageType::STRING; }
    if (strcmp(type.c_str(), "video") == 0) { return MessageType::VIDEO; }

    return MessageType::UNKNOWN;
}
