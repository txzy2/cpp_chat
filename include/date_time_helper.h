#pragma once

#include <ctime>
#include <string>

class DateTimeHelper
{
public:
    static std::string formatTime(std::time_t t, const std::string& format = "%Y-%m-%d %H:%M:%S")
    {
        char buf[64];
        std::tm tm{};

#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        std::strftime(buf, sizeof(buf), format.c_str(), &tm);
        return std::string(buf);
    }
};
