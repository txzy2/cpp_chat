#include "../include/cpp_test/message_types.h"

#include <cstring>
#include <string>

std::string enumToString(const MessageType type)
{
    switch (type)
    {
    case PHOTO:
        return "photo";
    case STRING:
        return "string";
    case VIDEO:
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
