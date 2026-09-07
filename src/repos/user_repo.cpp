#include "../../include/cpp_test/repos/user_repo.h"

#include <fstream>
#include <sstream>

void UserRepo::saveFriends(uint64_t userId, const std::vector<User>& friends) const
{
    std::ifstream inFile(filename_);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            std::istringstream iss(line);
            std::string storedId;
            std::getline(iss, storedId, '|');
            if (std::stoull(storedId) != userId)
            {
                lines.push_back(line);
            }
        }
    }
    inFile.close();

    std::ofstream outFile(filename_);
    for (const auto& l : lines)
    {
        outFile << l << "\n";
    }

    for (const auto& friend_ : friends)
    {
        outFile << userId << "|" << userToString(friend_) << "\n";
    }
}

auto UserRepo::loadFriends(uint64_t userId) const -> std::vector<User>
{
    std::vector<User> friends;
    std::ifstream file(filename_);
    if (!file.is_open())
    {
        return friends;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string storedId;
        std::getline(iss, storedId, '|');

        if (std::stoull(storedId) == userId)
        {
            std::string rest;
            std::getline(iss, rest);
            friends.push_back(stringToUser(rest));
        }
    }

    return friends;
}

bool UserRepo::areFriends(const uint64_t userId, const uint64_t friendId) const
{
    for (const auto friends = loadFriends(userId); const auto& f : friends)
    {
        if (f.getId() == friendId)
        {
            return true;
        }
    }
    return false;
}

std::string UserRepo::userToString(const User& user)
{
    std::ostringstream oss;
    oss << user.getId() << "|"
        << user.getName() << "|"
        << user.getUsername() << "|"
        << user.getEmail();
    return oss.str();
}

User UserRepo::stringToUser(const std::string& str)
{
    std::istringstream iss(str);
    std::string id, name, username, email;

    std::getline(iss, id, '|');
    std::getline(iss, name, '|');
    std::getline(iss, username, '|');
    std::getline(iss, email, '|');

    User u;
    u.setName(name);
    u.setUsername(username);
    u.setEmail(email);
    return u;
}
