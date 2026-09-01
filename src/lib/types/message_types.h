#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include <string>

enum MessageType
{
    PHOTO = 0,
    STRING,
    VIDEO,
    UNKNOWN
};

std::string enumToString(const MessageType type);
MessageType messageTypeToEnum(const std::string& type);

#endif